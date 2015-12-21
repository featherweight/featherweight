/*
    Copyright (c) 2014-2015 Wirebird Labs LLC. All rights reserved.

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

#include "ftw_nanomsg.h"

#include "upstream/src/pubsub.h"
#include "upstream/src/pipeline.h"

FTW_PRIVATE_SUPPORT void ftw_subscriber_async_recv_thread(void *arg);
FTW_PRIVATE_SUPPORT void ftw_nanomsg_shutdown_active_sockets(struct ftw_socket_callsite *inst);

int ftw_nanomsg_error(LStrHandle error_message)
{
    const char *human_readable_error;
    int current_error;

    current_error = errno;

    /*  The FTW library will explicitly handle a few errors, since "socket"
        could be a less misleading term than "file descriptors". */
    switch (current_error) {
    case EBADF:
        human_readable_error = "Invalid socket";
        break;
    case EMFILE:
        human_readable_error = "Too many open sockets";
        break;
    default:
        human_readable_error = nn_strerror(current_error);
        break;
    }

    ftw_support_CStr_to_LStrHandle(&error_message, human_readable_error, 1024);

    return current_error;
}

int ftw_nanomsg_setsockopt(const int socket_id, int level, int option, const void *value, size_t length)
{
    int rc;

    rc = nn_setsockopt(socket_id, level, option, value, length);

    return rc;
}

static void ftw_subscriber_async_recv_thread(void *arg)
{
    LStrHandle msg_sent_to_lv;
    struct ftw_socket *self;
    void *recv_buf;
    MgErr lv_err;
    int socket_err;
    int rc;

    ftw_assert(arg);

    /*  Create local pointer to arguments and notify launching process this thread is constructed. */
    self = ((struct ftw_socket *) arg);
    nn_sem_post(&self->init_sem);

    lv_err = mgNoErr;
    socket_err = 0;

    /*  This broker relays messages from the nanomsg socket into the LabVIEW incoming message queue. */
    while (!lv_err && !socket_err) {

        rc = nn_recv(self->id, &recv_buf, NN_MSG, 0);

        if (rc < 0) {
            socket_err = ((errno == ETIMEDOUT || errno == EAGAIN) ? 0 : errno);
            continue;
        }

        msg_sent_to_lv = (LStrHandle)DSNewHandle(rc);
        lv_err = ftw_support_buffer_to_LStrHandle(&msg_sent_to_lv, recv_buf, rc);

        /*  On the LabVIEW side, the handler is a an event registration, meaning
            LabVIEW will not effectively apply backpressure to the Publisher socket.
            For this reason, care must be taken that the Subscriber keep up with
            the Publisher, yet this consideration has long-existed for the LabVIEW
            developer (since, LV-native primitives will likewise cause a memory leak,
            when Event Registrations are allowed to grow without bound). */
        lv_err = PostLVUserEvent(self->lv_event, &msg_sent_to_lv);
        if (lv_err)
            continue;

        lv_err = DSDisposeHandle (msg_sent_to_lv);
        rc = nn_freemsg(recv_buf);
        if (rc) {
            socket_err = errno;
            continue;
        }
    }

    /*  Thread will silently prune on normal shutdown or fatal error. */
    nn_close(self->id);

    return;
}

int ftw_nanomsg_sync_server_start(struct ftw_socket_callsite **callsite,
    const char *addr, int linger, int max_recv_size, struct ftw_socket **sock)
{
    struct ftw_socket *inst;
    int rcb;
    int rcs;
    int rco;

    ftw_assert(*callsite);

    nn_mutex_lock(&(*callsite)->sync);

    rcs = nn_socket(AF_SP, NN_REP);

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

    rcb = nn_bind(rcs, addr);

    /*  Endpoint creation failure? */
    if (rcb < 0) {
        nn_close(rcs);
        *sock = NULL;
        nn_mutex_unlock(&(*callsite)->sync);
        return rcb;
    }

    inst = nn_alloc(sizeof(struct ftw_socket), "ftw_sync_server");
    alloc_assert(inst);

    inst->is_async = 0;
    inst->id = rcs;
    inst->callsite = *callsite;

    nn_list_item_init(&inst->item);
    nn_list_insert(&(*callsite)->active_sockets, &inst->item,
        nn_list_end(&(*callsite)->active_sockets));

    *sock = inst;

    (*callsite)->lifetime_sockets++;
    nn_mutex_unlock(&(*callsite)->sync);

    return 0;
}

int ftw_nanomsg_sync_server_await(struct ftw_socket ** const sock,
    const int timeout, LStrHandle request)
{
    struct ftw_socket const *s;
    MgErr lv_err;
    void *recv_buf;
    int rc;

    s = *sock;
    if (s == NULL) {
        errno = EBADF;
        return -1;
    }

    rc = nn_setsockopt(s->id, NN_SOL_SOCKET, NN_RCVTIMEO, &timeout, sizeof(timeout));
    if (rc < 0)
        return rc;

    recv_buf = NULL;

    rc = nn_recv(s->id, &recv_buf, NN_MSG, 0);

    if (rc < 0) {
        ftw_assert (recv_buf == NULL);
        return rc;
    }

    lv_err = ftw_support_buffer_to_LStrHandle(&request, recv_buf, rc);

    if (lv_err) {
        errno = lv_err + LV_USER_ERROR;
        rc = -1;
    }

    if (recv_buf)
        nn_freemsg(recv_buf);

    return rc;
}

int ftw_nanomsg_sync_server_reply(struct ftw_socket ** const sock,
    const int timeout, const LStrHandle response)
{
    struct ftw_socket const *s;
    const void *msg;
    size_t len;
    int rc;

    s = *sock;
    if (s == NULL) {
        errno = EBADF;
        return -1;
    }

    rc = nn_setsockopt(s->id, NN_SOL_SOCKET, NN_SNDTIMEO, &timeout, sizeof(timeout));
    if (rc < 0)
        return rc;

    msg = LHStrBuf(response);
    len = LHStrLen(response);

    rc = nn_send(s->id, msg, len, 0);

    return rc;
}

int ftw_nanomsg_sync_server_stop(struct ftw_socket ** const sock)
{
    return ftw_socket_destroy(sock);
}

int ftw_nanomsg_connector_connect(struct ftw_socket_callsite **callsite, const char *addr,
    int linger, int max_recv_size, struct ftw_socket **sock)
{
    struct ftw_socket *inst;
    int rcs;
    int rco;
    int rcc;

    ftw_assert(*callsite);

    nn_mutex_lock(&(*callsite)->sync);

    rcs = nn_socket(AF_SP, NN_REQ);

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

    rcc = nn_connect(rcs, addr);

    /*  Endpoint creation failure? */
    if (rcc < 0) {
        nn_close(rcs);
        *sock = NULL;
        nn_mutex_unlock(&(*callsite)->sync);
        return rcc;
    }

    inst = nn_alloc(sizeof(struct ftw_socket), "ftw_connector");
    alloc_assert(inst);

    inst->id = rcs;
    inst->callsite = *callsite;
    inst->is_async = 0;

    nn_list_item_init(&inst->item);
    nn_list_insert(&(*callsite)->active_sockets, &inst->item,
        nn_list_end(&(*callsite)->active_sockets));

    *sock = inst;

    (*callsite)->lifetime_sockets++;
    nn_mutex_unlock(&(*callsite)->sync);

    return 0;

}

int ftw_nanomsg_connector_ask(struct ftw_socket ** const sock, int send_timeout,
    int recv_timeout, const LStrHandle request, LStrHandle response)
{
    int rc;
    struct nn_iovec iov;
    struct nn_msghdr hdr;
    void *recv_buf;
    MgErr resize_err;
    struct ftw_socket const *s;

    s = *sock;

    if (s == NULL) {
        errno = EBADF;
        return -1;
    }

    iov.iov_base = LHStrBuf(request);
    iov.iov_len = LHStrLen(request);

    hdr.msg_iov = &iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = NULL;
    hdr.msg_controllen = 0;

    rc = nn_setsockopt(s->id, NN_SOL_SOCKET, NN_SNDTIMEO, &send_timeout, sizeof(send_timeout));
    if (rc < 0)
        return rc;

    rc = nn_setsockopt(s->id, NN_SOL_SOCKET, NN_RCVTIMEO, &recv_timeout, sizeof(recv_timeout));
    if (rc < 0)
        return rc;

    rc = nn_sendmsg(s->id, &hdr, 0);

    if (rc >= 0) {
        recv_buf = NULL;
        iov.iov_base = &recv_buf;
        iov.iov_len = NN_MSG;

        hdr.msg_iov = &iov;
        hdr.msg_iovlen = 1;
        hdr.msg_control = NULL;
        hdr.msg_controllen = 0;

        rc = nn_recvmsg(s->id, &hdr, 0);

        if (rc >= 0) {
            resize_err = ftw_support_buffer_to_LStrHandle(&response, recv_buf, rc);
            if (resize_err != mgNoErr) {
                errno = resize_err + LV_USER_ERROR;
                rc = -1;
            }
        }

        if (recv_buf)
            nn_freemsg(recv_buf);
    }

    return rc;
}

int ftw_nanomsg_connector_disconnect(struct ftw_socket ** const sock)
{
    return ftw_socket_destroy(sock);
}

int ftw_publisher_construct(struct ftw_socket_callsite **callsite, const char *addr,
    int linger, struct ftw_socket **sock)
{
    struct ftw_socket *inst;
    int rcs;
    int rco;
    int rcb;

    ftw_assert(*callsite);

    nn_mutex_lock(&(*callsite)->sync);

    rcs = nn_socket(AF_SP, NN_PUB);

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

    rcb = nn_bind(rcs, addr);

    /*  Endpoint creation failure? */
    if (rcb < 0) {
        nn_close(rcs);
        *sock = NULL;
        nn_mutex_unlock(&(*callsite)->sync);
        return rcb;
    }

    inst = nn_alloc(sizeof(struct ftw_socket), "ftw_publisher");
    alloc_assert(inst);

    inst->id = rcs;
    inst->callsite = *callsite;
    inst->is_async = 0;

    nn_list_item_init(&inst->item);
    nn_list_insert(&(*callsite)->active_sockets, &inst->item,
        nn_list_end(&(*callsite)->active_sockets));

    *sock = inst;

    (*callsite)->lifetime_sockets++;
    nn_mutex_unlock(&(*callsite)->sync);

    return 0;

}

int ftw_publisher_publish(struct ftw_socket ** const sock, int send_timeout, ConstLStrH message)
{
    struct ftw_socket const *s;
    int rc;
    const void *buf;
    size_t len;

    s = *sock;

    if (s == NULL) {
        errno = EBADF;
        return -1;
    }

    buf = LHStrBuf(message);
    len = LHStrLen(message);

    rc = nn_setsockopt(s->id, NN_SOL_SOCKET, NN_SNDTIMEO, &send_timeout, sizeof(send_timeout));
    if (rc < 0)
        return rc;

    rc = nn_send(s->id, buf, len, 0);

    return rc;
}

int ftw_publisher_destroy(struct ftw_socket ** const sock)
{
    return ftw_socket_destroy(sock);
}


int ftw_subscriber_construct(struct ftw_socket_callsite **callsite, LVUserEventRef *lv_event,
    const char *addr, int linger, int max_recv_size, struct ftw_socket **sock)
{
    struct ftw_socket *inst;
    int rcc;
    int rcs;
    int rco;

    ftw_assert(*callsite);

    nn_mutex_lock(&(*callsite)->sync);

    rcs = nn_socket(AF_SP, NN_SUB);

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

    rcc = nn_connect(rcs, addr);

    /*  Endpoint creation failure? */
    if (rcc < 0) {
        nn_close(rcs);
        *sock = NULL;
        nn_mutex_unlock(&(*callsite)->sync);
        return rcc;
    }

    rco = nn_setsockopt (rcs, NN_SUB, NN_SUB_SUBSCRIBE, "", 0);
    if (rco < 0) {
        nn_close(rcs);
        *sock = NULL;
        nn_mutex_unlock(&(*callsite)->sync);
        return rco;
    }

    inst = nn_alloc(sizeof(struct ftw_socket), "ftw_subscriber");
    alloc_assert(inst);

    inst->is_async = 1;
    inst->lv_event = *lv_event;
    inst->id = rcs;
    inst->callsite = *callsite;

    nn_list_item_init(&inst->item);
    nn_list_insert(&(*callsite)->active_sockets, &inst->item,
        nn_list_end(&(*callsite)->active_sockets));

    /*  Launch thread and wait for it to initialize. */
    nn_sem_init(&inst->init_sem);
    nn_thread_init(&inst->thread, ftw_subscriber_async_recv_thread, inst);
    nn_sem_wait(&inst->init_sem);

    *sock = inst;

    (*callsite)->lifetime_sockets++;
    nn_mutex_unlock(&(*callsite)->sync);

    return 0;
}

int ftw_subscriber_destroy(struct ftw_socket ** const sock)
{
    return ftw_socket_destroy(sock);
}

int ftw_socket_close(struct ftw_socket * const sock)
{
    int rc;
    if (sock->is_async) {
        rc = nn_close(sock->id);
        nn_thread_term(&sock->thread);
        nn_sem_term(&sock->init_sem);
    }
    else {
        rc = nn_close(sock->id);
    }
    return rc;
}

int ftw_socket_destroy(struct ftw_socket ** const sock)
{
    struct ftw_socket *s;
    int rc;

    s = *sock;
    *sock = NULL;

    if (s == NULL) {
        errno = EBADF;
        rc = -1;
    }
    else {
        nn_mutex_lock(&(s->callsite)->sync);
        rc = ftw_socket_close(s);
        nn_list_erase(&(s->callsite)->active_sockets, &s->item);
        nn_mutex_unlock(&(s->callsite)->sync);
        nn_free(s);
    }

    return rc;
}

MgErr ftw_nanomsg_reserve(struct ftw_socket_callsite **inst)
{
    static int callsite = 0;

    /*  Creates a list of socket instances for each CLFN callsite. */
    if (*inst == NULL) {
        callsite++;
        ftw_debug("Reserving: %d", callsite);
        *inst = nn_alloc(sizeof(struct ftw_socket_callsite), "callsite_socket_list");
        alloc_assert(*inst);
        nn_mutex_init(&(*inst)->sync);
        nn_mutex_lock(&(*inst)->sync);
        nn_list_init(&(*inst)->active_sockets);
        (*inst)->id = callsite;
        (*inst)->lifetime_sockets = 0;
        nn_mutex_unlock(&(*inst)->sync);
    }
    else {
        ftw_assert_unreachable("Reserve happened twice; this is a problem with LabVIEW.");
    }

    return mgNoErr;
}

MgErr ftw_nanomsg_unreserve(struct ftw_socket_callsite **inst)
{
    /*  LabVIEW retains the lifetime of this pointer for each session. For this reason,
        NULL its value so that it does not continue to point to freed memory. */

    if (*inst) {
        ftw_nanomsg_shutdown_active_sockets(*inst);
        nn_mutex_term(&(*inst)->sync);
        ftw_debug("Unreserving: %d; Sockets created: %d", (*inst)->id, (*inst)->lifetime_sockets);
        nn_free(*inst);
        *inst = NULL;
    }
    else {
        ftw_debug("No-op socket callsite unloaded.");
    }

    return mgNoErr;
}

MgErr ftw_nanomsg_abort(struct ftw_socket_callsite **inst)
{

    ftw_assert(*inst);

    ftw_nanomsg_shutdown_active_sockets(*inst);

    return mgNoErr;
}

static void ftw_nanomsg_shutdown_active_sockets(struct ftw_socket_callsite *callsite)
{
    struct ftw_socket *sock;
    struct nn_list_item *it;

    nn_mutex_lock(&callsite->sync);

    ftw_debug("Cleaning up %d", callsite->id);

    it = nn_list_begin(&callsite->active_sockets);
    while (it != NULL) {
        sock = nn_cont(it, struct ftw_socket, item);
        ftw_debug("Cleaning up active socket: %04d", sock->id);
        ftw_socket_close(sock);
        it = nn_list_erase(&callsite->active_sockets, it);
    }

    nn_list_term(&callsite->active_sockets);
    nn_mutex_unlock(&callsite->sync);

    return;
}