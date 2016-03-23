/*
    Copyright (c) 2014-2016 Wirebird Labs LLC. All rights reserved.

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

FTW_PRIVATE_SUPPORT void ftw_socket_inbox_async_recv_worker(void *arg);

const char *ftw_version(void)
{
    return "0.7.0";
}

void ftw_lvmem(int64 *ds_bytes_allocated)
{
    MgErr lv_err;
    MemStatRec stats;
    lv_err = DSMemStats(&stats);
    if (lv_err)
        *ds_bytes_allocated = -1;
    else
        *ds_bytes_allocated = (int64)stats.totAllocSize;
    return;
}

void ftw_socket_inbox_async_recv_worker(void *arg)
{
    /*  Opaque pointer into ftw_incoming_request structure using LabVIEW-safe type for PostLVUserEvent. */
    int64 opaque;
    struct ftw_incoming_request *incoming;
    struct ftw_socket *self;
    struct nn_iovec iov;
    struct nn_msghdr msg;
    void *msg_ptr;
    void *hdr_ptr;
    MgErr lv_err;
    int socket_err;
    int rc;

    /*  Notify launching process this thread is constructed. */
    ftw_assert(arg);
    self = (struct ftw_socket *) arg;
    nn_sem_post(&self->ready);

    lv_err = mgNoErr;
    socket_err = 0;

    /*  This broker relays messages from the nanomsg socket into the LabVIEW incoming message queue. */
    while (!lv_err && !socket_err) {

        /* Created here, this incoming request should be freed once the response is sent. */
        incoming = nn_alloc(sizeof(struct ftw_incoming_request), "ftw_incoming_request");
        if (incoming == NULL) {
            lv_err = mFullErr;
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

            incoming->sock = self;
            incoming->msg_piped_to_lv = &self->ready_for_next_msg;
            incoming->msg_ptr = msg_ptr;
            incoming->msg_len = nn_chunk_size(msg_ptr);
            incoming->hdr_ptr = hdr_ptr;
            incoming->hdr_len = nn_chunk_size(hdr_ptr);

            opaque = (int64)incoming;

            /*  On the LabVIEW side, the handler is a an Event Handler Structure, which
                applies no backpressure since the event queue cannot be limited for dynamic
                events. For this reason, a semaphore is introduced to simulate blocking backpressure,
                where the semaphore is posted once the Inbox Message Router receives the message. */
            nn_sem_wait(&self->ready_for_next_msg);
            lv_err = PostLVUserEvent(self->msg_to_lv_event, &opaque);
        }
        else {
            /*  Treat timeouts as non-fatal. Anything else will stop this thread. */
            socket_err = ((errno == ETIMEDOUT || errno == EAGAIN) ? 0 : errno);
        }
    }

    /*  Posting a NULL pointer signals the LabVIEW Message Router to shutdown. */
    opaque = (int64) NULL;
    lv_err = PostLVUserEvent(self->msg_to_lv_event, &opaque);

    return;
}

int ftw_socket_inbox_construct(struct ftw_socket_callsite **callsite, LVUserEventRef *msg_to_lv_event,
    struct ftw_socket **sock, const LStrHandleArray **addresses, int linger, int max_recv_size)
{
    struct ftw_socket *inst;
    char *addr;
    int rcb;
    int rcs;
    int rco;
    int i;

    /*  Preconditions expected of LabVIEW. */
    ftw_assert(callsite && *callsite && addresses && *addresses && msg_to_lv_event && sock);
    nn_mutex_lock(&(*callsite)->sync);

    rcs = nn_socket(AF_SP_RAW, NN_REP);

    /*  Socket creation failure? */
    if (rcs < 0) {
        *sock = NULL;
        nn_mutex_unlock(&(*callsite)->sync);
        return rcs;
    }

    rco = nn_setsockopt(rcs, NN_SOL_SOCKET, NN_LINGER, &linger, sizeof(linger));
    if (rco < 0) {
        *sock = NULL;
        nn_mutex_unlock(&(*callsite)->sync);
        return rco;
    }

    rco = nn_setsockopt(rcs, NN_SOL_SOCKET, NN_RCVMAXSIZE, &max_recv_size, sizeof(max_recv_size));
    if (rco < 0) {
        *sock = NULL;
        nn_mutex_unlock(&(*callsite)->sync);
        return rco;
    }

    for (i = 0; i < (*addresses)->dimsize; i++) {
        addr = ftw_support_LStrHandle_to_CStr((*addresses)->element[i]);
        rcb = nn_bind(rcs, addr);
        free (addr);
        if (rcb < 0) {
            nn_close(rcs);
            *sock = NULL;
            nn_mutex_unlock(&(*callsite)->sync);
            return rcb;
        }
    }

    inst = nn_alloc(sizeof(struct ftw_socket), "ftw_inbox");
    alloc_assert(inst);

    inst->is_async = 1;
    inst->msg_to_lv_event = *msg_to_lv_event;
    inst->id = rcs;
    inst->callsite = *callsite;

    nn_list_item_init(&inst->item);
    nn_list_insert(&(*callsite)->active_sockets, &inst->item,
        nn_list_end(&(*callsite)->active_sockets));

    /*  Launch thread and wait for it to initialize. */
    nn_sem_init(&inst->ready);
    nn_sem_init(&inst->ready_for_next_msg);
    nn_thread_init(&inst->thread, ftw_socket_inbox_async_recv_worker, inst);
    nn_sem_wait(&inst->ready);

    /*  Assume that the Inbox Message Router on LabVIEW side is always ready for first message. */
    nn_sem_post(&inst->ready_for_next_msg);

    *sock = inst;

    (*callsite)->lifetime_sockets++;
    nn_mutex_unlock(&(*callsite)->sync);

    return 0;
}

int ftw_socket_inbox_recv(struct ftw_incoming_request *incoming, json_t **json_msg, size_t flags, int64 *err_line,
    int64 *err_column, int64 *err_position, LStrHandle err_source, LStrHandle err_hint)
{
    json_error_t err;
    int rc;

    /*  Preconditions expected of LabVIEW. */
    ftw_assert(incoming && incoming->msg_ptr && incoming->msg_piped_to_lv && json_msg);

    /*  Notify async receive thread that it can pipeline the next message into the LVEvent. */
    nn_sem_post(incoming->msg_piped_to_lv);

    *json_msg = json_loadb(incoming->msg_ptr, incoming->msg_len, flags, &err);

    rc = nn_freemsg(incoming->msg_ptr);
    ftw_assert(rc == 0);

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

int ftw_socket_inbox_reply(json_t *response, struct ftw_incoming_request *req, const int timeout)
{
    struct ftw_socket const *s;
    struct nn_iovec iov;
    struct nn_msghdr hdr;
    size_t hdr_len;
    void *hdr_ptr;
    char *buffer;
    int rc;

    if (req) {
        s = req->sock;
        hdr_len = req->hdr_len;
        hdr_ptr = req->hdr_ptr;
        nn_free(req);
    }
    else {
        ftw_json_destroy(response);
        errno = EBADF;
        return -1;
    }

    if (hdr_ptr == NULL) {
        ftw_json_destroy(response);
        errno = EBADF;
        return -1;
    }
    
    if (s == NULL) {
        nn_freemsg(hdr_ptr);
        ftw_json_destroy(response);
        errno = EBADF;
        return -1;
    }

    buffer = json_dumps(response, JSON_ALLOW_NUL);
    ftw_json_destroy(response);

    if (buffer == NULL) {
        nn_freemsg(hdr_ptr);
        errno = EBADF;
        return -1;
    }

    iov.iov_base = buffer;
    iov.iov_len = strlen(buffer);

    hdr.msg_iov = &iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = hdr_ptr;
    hdr.msg_controllen = hdr_len;

    rc = nn_setsockopt(s->id, NN_SOL_SOCKET, NN_SNDTIMEO, &timeout, sizeof(timeout));
    if (rc < 0) {
        free(buffer);
        nn_freemsg(hdr_ptr);
        return rc;
    }

    rc = nn_sendmsg(s->id, &hdr, 0);
    free(buffer);
    nn_freemsg(hdr_ptr);
    return rc;
}
