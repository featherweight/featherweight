/*
    Copyright (c) 2014-2017 Wirebird Labs LLC. All rights reserved.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom
    the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "ftw_framework.h"
#include "../nanomsg/upstream/src/reqrep.h"

FTW_PRIVATE_SUPPORT void ftw_socket_inbox_async_recv_worker(void *arg);

const char *ftw_version(void)
{
    return FTW_VERSION_TEXT;
}


void ftw_resource_usage(double *user_cpu_time, double *system_cpu_time, double *uptime, uint64_t *hi_res_relative_time,
    uint64_t *peak_working_set, uint64_t *lv_dataspace_size, uint64_t *hard_page_faults)
{
    uv_rusage_t rusage;
    double up;
    MemStatRec stats;
    MgErr lvrc;
    int rc;

    lvrc = DSMemStats(&stats);
    if (lvrc == mgNoErr) {
        *lv_dataspace_size = (uint64_t)stats.totAllocSize;
    }

    rc = uv_getrusage(&rusage);
    if (rc == 0) {
        *user_cpu_time = (double)rusage.ru_utime.tv_sec + rusage.ru_utime.tv_usec * 1e-6;
        *system_cpu_time = (double)rusage.ru_stime.tv_sec + rusage.ru_stime.tv_usec * 1e-6;
        *peak_working_set = rusage.ru_maxrss;
        *hard_page_faults = rusage.ru_majflt;
    }

    rc = uv_uptime(&up);
    if (rc == 0) {
        *uptime = up;
    }

    *hi_res_relative_time = uv_hrtime();

    return;
}


void ftw_socket_inbox_async_recv_worker(void *arg)
{
    /*  Opaque pointer into ftw_incoming_request structure using LabVIEW-safe type for PostLVUserEvent. */
    int64 opaque;
    struct ftw_incoming_request *incoming;
    struct ftw_socket_inbox *self;
    struct nn_iovec iov;
    struct nn_msghdr msg;
    void *msg_ptr;
    void *hdr_ptr;
    MgErr lvrc;
    int socket_err;
    int rc;

    /*  Notify launching process this thread is constructed. */
    ftw_assert(arg);
    self = (struct ftw_socket_inbox *) arg;
    uv_sem_post(&self->initialized);

    lvrc = mgNoErr;
    socket_err = EFTWOK;

    /*  This broker relays messages from the nanomsg socket into the LabVIEW incoming message queue. */
    while (lvrc == mgNoErr && socket_err == EFTWOK) {

        /* Created here, this incoming request should be freed once the response is sent. */
        incoming = ftw_malloc(sizeof(struct ftw_incoming_request));
        if (incoming == NULL) {
            lvrc = mFullErr;
            continue;
        }
        
        iov.iov_base = &msg_ptr;
        iov.iov_len = NN_MSG;

        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_control = &hdr_ptr;
        msg.msg_controllen = NN_MSG;

        rc = nn_recvmsg(self->id, &msg, 0);
        if (rc >= 0) {

            incoming->inbox = self;
            incoming->msg_ptr = msg_ptr;
            incoming->msg_len = nn_chunk_size(msg_ptr);
            incoming->hdr_ptr = hdr_ptr;
            incoming->hdr_len = nn_chunk_size(hdr_ptr);

            opaque = (int64)incoming;
            lvrc = PostLVUserEvent(self->incoming_msg_notifier_event, &opaque);
            ftw_assert(lvrc == mgNoErr);

            /*  On the LabVIEW side, the handler is a an Event Handler Structure, which
                applies no backpressure since the event queue cannot be limited for dynamic
                events. For this reason, a semaphore is introduced to simulate blocking backpressure,
                where the semaphore is posted once the Inbox Message Router receives the message. */
            uv_sem_wait(&self->msg_acknowledged);
        }
        else {
            /*  Treat timeouts as non-fatal. Anything else will stop this thread. */
            socket_err = ((errno == ETIMEDOUT || errno == EAGAIN) ? EFTWOK : -errno);
        }
    }

    /*  Posting a NULL pointer signals the LabVIEW Message Router to shutdown. */
    opaque = (int64) NULL;
    lvrc = PostLVUserEvent(self->incoming_msg_notifier_event, &opaque);
    ftw_assert(lvrc == mgNoErr);

    /*  Wait for the Message Router to unload. */
    uv_sem_wait(&self->deinitialized);

    return;
}


ftwrc ftw_actor_inbox_construct(struct ftw_socket_inbox **inst, LVUserEventRef *msg_to_lv_event,
    struct ftw_socket_inbox **sock, const LStrHandleArray **addresses, int max_recv_size)
{
    ftwrc rc;
    char *addr;
    int rcb;
    int rcs;
    int rco;
    int i;

    /*  Preconditions expected of LabVIEW. */
    ftw_assert(inst && *inst && addresses && *addresses && msg_to_lv_event && sock);

    /*  Preconditions expected of FTW. The vast majority of normal operating cases, state will be UNINITIALIZED, yet it's possible
        to contrive rare instances of ZOMBIFIED. Here, the Inbox would need to be destroyed by an Actor Instance that immediately
        shuts down after launch, and when the scheduler has chosen to do so even prior to its async Inbox being fully initialized,
        which only happens when the CPU is under extreme duress and the execution system threads are exhausted. Even then, anecdotally
        it takes an even more contrived source of stress, such as turning on Profile Performance and Memory to further exacerbate the race. */
    ftw_assert((*inst)->state != ACTIVE);

    rcs = nn_socket(AF_SP_RAW, NN_REP);

    /*  Socket creation failure? */
    if (rcs < 0) {
        *sock = NULL;
        return errno;
    }

    rco = nn_setsockopt(rcs, NN_SOL_SOCKET, NN_RCVMAXSIZE, &max_recv_size, sizeof(max_recv_size));
    if (rco < 0) {
        nn_close(rcs);
        *sock = NULL;
        return errno;
    }

    for (i = 0; i < (*addresses)->dimsize; i++) {
        addr = ftw_support_LStrHandle_to_CStr((*addresses)->element[i]);
        rcb = nn_bind(rcs, addr);
        rc = ftw_free (addr);
        ftw_assert_ok(rc);
        if (rcb < 0) {
            nn_close(rcs);
            *sock = NULL;
            return errno;
        }
    }

    /*  Locking the object has been deferred as long as possible until this point. */
    uv_mutex_lock(&(*inst)->lock);

    /*  Early return in the unlikely race when an inbox is destroyed in a concurrent thread immediately after being created. */
    if ((*inst)->state == ZOMBIFIED) {
        uv_mutex_unlock(&(*inst)->lock);
        *sock = NULL;
        return EBADF;
    }

    ftw_assert((*inst)->state == UNINITIALIZED);

    (*inst)->incoming_msg_notifier_event = *msg_to_lv_event;
    (*inst)->id = rcs;

    /*  Launch thread and wait for it to initialize. */
    ftw_assert_ok(uv_sem_init(&(*inst)->deinitialized, 0));
    ftw_assert_ok(uv_sem_init(&(*inst)->initialized, 0));
    ftw_assert_ok(uv_sem_init(&(*inst)->msg_acknowledged, 0));
    uv_thread_create(&(*inst)->async_recv_thread, ftw_socket_inbox_async_recv_worker, *inst);
    uv_sem_wait(&(*inst)->initialized);

    (*inst)->state = ACTIVE;
    *sock = *inst;

    uv_mutex_unlock(&(*inst)->lock);

    return EFTWOK;
}


ftwrc ftw_actor_inbox_recv(struct ftw_incoming_request *incoming, json_t **json_msg, size_t flags,
    int64 *err_line, int64 *err_column, int64 *err_position, LStrHandle err_source, LStrHandle err_hint)
{
    json_error_t err;
    int rc;

    /*  Preconditions expected of LabVIEW. */
    ftw_assert(incoming && incoming->msg_ptr && incoming->inbox && json_msg);

    /*  Notify async receive thread that it can pipeline the next message into the LVEvent. */
    uv_sem_post(&incoming->inbox->msg_acknowledged);

    *json_msg = json_loadb(incoming->msg_ptr, incoming->msg_len, flags, &err);

    rc = nn_freemsg(incoming->msg_ptr);

    /*  Invalid JSON in the buffer is an error condition indicated by NULL. */
    if (*json_msg == NULL) {
        *err_line = err.line;
        *err_column = err.column;
        *err_position = err.position;
        ftw_support_CStr_to_LStrHandle(&err_source, err.source, sizeof(err.source));
        ftw_support_CStr_to_LStrHandle(&err_hint, err.text, sizeof(err.text));
        *json_msg = json_object();
    }

    return rc;
}


ftwrc ftw_actor_inbox_reply(json_t *response, struct ftw_incoming_request *req, const int timeout)
{
    struct ftw_socket_inbox *s;
    struct nn_iovec iov;
    struct nn_msghdr hdr;
    size_t hdr_len;
    void *hdr_ptr;
    char *buffer;
    int rc;

    if (req == NULL) {
        ftw_json_destroy(response);
        return EBADF;
    }

    s = req->inbox;
    hdr_len = req->hdr_len;
    hdr_ptr = req->hdr_ptr;
    ftw_assert_ok(ftw_free(req));

    if (hdr_ptr == NULL) {
        ftw_json_destroy(response);
        return EBADF;
    }
    
    if (s == NULL) {
        nn_freemsg(hdr_ptr);
        ftw_json_destroy(response);
        return EBADF;
    }

    buffer = json_dumps(response, JSON_ALLOW_NUL);
    ftw_json_destroy(response);

    if (buffer == NULL) {
        nn_freemsg(hdr_ptr);
        return EBADF;
    }

    iov.iov_base = buffer;
    iov.iov_len = strlen(buffer);
    ftw_assert(iov.iov_len > 0);

    hdr.msg_iov = &iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = hdr_ptr;
    hdr.msg_controllen = hdr_len;

    /* Acquire the lock to guarantee the socket is still active. */
    uv_mutex_lock(&s->lock);

    if (s->state != ACTIVE) {
        free(buffer);
        nn_freemsg(hdr_ptr);
        uv_mutex_unlock(&s->lock);
        return EBADF;
    }

    rc = nn_setsockopt(s->id, NN_SOL_SOCKET, NN_SNDTIMEO, &timeout, sizeof(timeout));
    if (rc < 0) {
        free(buffer);
        nn_freemsg(hdr_ptr);
        uv_mutex_unlock(&s->lock);
        return errno;
    }

    rc = nn_sendmsg(s->id, &hdr, 0);

    free(buffer);
    nn_freemsg(hdr_ptr);

    uv_mutex_unlock(&s->lock);

    return (rc ? errno : EFTWOK);
}


ftwrc ftw_actor_inbox_shutdown(struct ftw_socket_inbox ** const sock)
{
    uint64_t time;
    double elapsed_time;
    int rc;

    /*  Preconditions expected of LabVIEW. */
    ftw_assert(sock);

    if (*sock == NULL) {
        return EBADF;
    }

    time = uv_hrtime();

    /*  Wait until any concurrent operations have completed by obtaining the lock. */
    uv_mutex_lock(&(*sock)->lock);

    /*  Socket shutdown was requested even before initialization was complete, so return early since no resources need to be destroyed. */
    if ((*sock)->state == UNINITIALIZED) {
        ftw_debug("Uninitialized Inbox abandoned.");
        uv_mutex_unlock(&(*sock)->lock);
        return EFTWOK;
    }

    /*  With lock still held, zombify then close the socket. */
    ftw_assert((*sock)->state == ACTIVE);
    (*sock)->state = ZOMBIFIED;
    rc = nn_close((*sock)->id);
    uv_mutex_unlock(&(*sock)->lock);


    /*  Let async inbox thread know it's OK to unload since LV will no longer be using its stack-allocated memory. */
    uv_sem_post(&(*sock)->deinitialized);

    /*  Wait for async inbox thread to complete, so that we know it's not using any of the inbox object's members. */
    ftw_assert_ok(uv_thread_join(&(*sock)->async_recv_thread));

    /*  Acquire lock a final time, since closing the socket should guarantee that no more async I/O is in progress.
        Destroy inbox resources and mark the object allocation as unused. It may be reused again if LV chooses to reuse a clone VI. */
    uv_mutex_lock(&(*sock)->lock);
    uv_sem_destroy(&(*sock)->msg_acknowledged);
    uv_sem_destroy(&(*sock)->initialized);
    uv_sem_destroy(&(*sock)->deinitialized);
    (*sock)->state = UNINITIALIZED;
    uv_mutex_unlock(&(*sock)->lock);

    time = uv_hrtime() - time;
    elapsed_time = time / 1000000000.0;
    ftw_debug("Inbox Shutdown time: %.3fsec", elapsed_time);

    return (rc ? errno : EFTWOK);
}


MgErr ftw_actor_inbox_reserve(struct ftw_socket_inbox **inst)
{
    /*  Preconditions expected of LabVIEW. */
    ftw_assert(inst && *inst == NULL);

    ftw_debug("Reserving ActorInbox.");
    *inst = ftw_malloc(sizeof(struct ftw_socket_inbox));
    if (*inst == NULL) {
        return mFullErr;
    }
    
    ftw_assert_ok(uv_mutex_init(&(*inst)->lock));
    ftw_assert_ok(uv_mutex_trylock(&(*inst)->lock));
    (*inst)->state = UNINITIALIZED;
    uv_mutex_unlock(&(*inst)->lock);

    return mgNoErr;
}


MgErr ftw_actor_inbox_unreserve(struct ftw_socket_inbox **inst)
{
    /*  Preconditions expected of LabVIEW. */
    ftw_assert(inst);

    /*  LabVIEW retains the lifetime of this pointer as long as the DLL remains loaded. */
    if (*inst) {
        ftw_debug("Unreserving ActorInbox.");
        uv_mutex_lock(&(*inst)->lock);
        ftw_assert((*inst)->state == UNINITIALIZED || (*inst)->state == ZOMBIFIED);
        uv_mutex_unlock(&(*inst)->lock);
        uv_mutex_destroy(&(*inst)->lock);
        ftw_assert_ok(ftw_free(*inst));
        *inst = NULL;
    }
    else {
        ftw_debug("No-op ActorInbox unreserve.");
    }

    return mgNoErr;
}


MgErr ftw_actor_inbox_abort(struct ftw_socket_inbox **inst)
{
    /*  Preconditions expected of LabVIEW. */
    ftw_assert(inst && *inst);

    ftw_debug("Aborting ActorInbox.");
    ftw_actor_inbox_shutdown(inst);

    return mgNoErr;
}
