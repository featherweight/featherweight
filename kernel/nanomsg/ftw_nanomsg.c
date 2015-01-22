/*
    Copyright (c) 2014 Wirebird Labs LLC. All rights reserved.

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

#include "upstream/src/reqrep.h"
#include "upstream/src/pubsub.h"
#include "upstream/src/pipeline.h"
#include "upstream/src/survey.h"
#include "upstream/src/pair.h"
#include "upstream/src/bus.h"

#include "upstream/src/utils/alloc.h"
#include "upstream/src/utils/chunk.h"
#include "upstream/src/utils/cont.h"

static void ftw_nanomsg_async_recv_thread(void *arg);
static void ftw_nanomsg_shutdown_active_sockets(struct ftw_socket_callsite *inst);

int ftw_nanomsg_error(LStrHandle error_message)
{
    const char* human_readable_error;
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

    ftw_support_copy_to_LStrHandle(error_message, human_readable_error, strlen(human_readable_error));

    return errno;
}

const char *ftw_nanomsg_version(void)
{
    return "0.5.0-1005";
}

int ftw_nanomsg_socket(struct ftw_socket_callsite **callsite, const int scalability_protocol,
    const LVBoolean *raw, const int linger, const int sndbuf, const int rcvbuf)
{
    int rcs;
    int rc;
    int domain;
    int protocol;

    int available_protocols[10] = { NN_REP, NN_REQ, NN_PUB, NN_SUB, NN_PUSH, NN_PULL, NN_SURVEYOR, NN_RESPONDENT, NN_PAIR, NN_BUS };

    if (scalability_protocol < 0 || scalability_protocol >= sizeof(available_protocols) / sizeof(available_protocols[0]))
    {
        errno = EINVAL;
        return -1;
    }

    domain = (*raw == LVBooleanFalse) ? AF_SP : AF_SP_RAW;
    protocol = available_protocols[scalability_protocol];

    rcs = nn_socket(domain, protocol);

    if (rcs < 0)
        return rcs;

    rc = nn_setsockopt(rcs, NN_SOL_SOCKET, NN_LINGER, &linger, sizeof(linger));
    if (rc < 0)
        return rc;

    rc = nn_setsockopt(rcs, NN_SOL_SOCKET, NN_SNDBUF, &sndbuf, sizeof(sndbuf));
    if (rc < 0)
        return rc;

    rc = nn_setsockopt(rcs, NN_SOL_SOCKET, NN_RCVBUF, &rcvbuf, sizeof(rcvbuf));
    if (rc < 0)
        return rc;
    
    return rcs;
}

int ftw_nanomsg_setsockopt(const int socket_id, int level, int option, const void *value, size_t length)
{
    int rc;

    rc = nn_setsockopt(socket_id, level, option, value, length);

    return rc;
}

int ftw_nanomsg_connect(const int socket_id, const char *addr)
{
    int rc;

    rc = nn_connect(socket_id, addr);

    return rc;
}

int ftw_nanomsg_bind(const int socket_id, const char *addr)
{
    int rc;

    rc = nn_bind(socket_id, addr);

    return rc;
}

int ftw_nanomsg_send(const int socket_id, const int timeout, const LStrHandle outgoing_msg, LVBoolean *timed_out)
{
    int rc;
    struct nn_iovec iov;
    struct nn_msghdr hdr;

    iov.iov_base = LHStrBuf(outgoing_msg);
    iov.iov_len = LHStrLen(outgoing_msg);

    memset(&hdr, 0, sizeof(hdr));
    hdr.msg_iov = &iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = NULL;
    hdr.msg_controllen = 0;

    nn_setsockopt(socket_id, NN_SOL_SOCKET, NN_SNDTIMEO, &timeout, sizeof(timeout));

    rc = nn_sendmsg(socket_id, &hdr, 0);

    *timed_out = ftw_nanomsg_timeout(rc);

    return rc;
}

int ftw_nanomsg_recv(const int socket_id, const int timeout, LStrHandle incoming_msg, LVBoolean *timed_out)
{
    int rc;
    struct nn_iovec iov;
    struct nn_msghdr hdr;
    void *recv_buf;
    MgErr resize_err;

    recv_buf = NULL;
    iov.iov_base = &recv_buf;
    iov.iov_len = NN_MSG;

    memset(&hdr, 0, sizeof(hdr));
    hdr.msg_iov = &iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = NULL;
    hdr.msg_controllen = 0;

    rc = nn_setsockopt(socket_id, NN_SOL_SOCKET, NN_RCVTIMEO, &timeout, sizeof(timeout));

    if (rc < 0)
        return rc;

    rc = nn_recvmsg(socket_id, &hdr, 0);

    if (rc >= 0) {
        resize_err = ftw_support_copy_to_LStrHandle(incoming_msg, recv_buf, rc);
        if (resize_err != mgNoErr) {
            errno = resize_err + LV_USER_ERROR;
            rc = -1;
        }
    }

    if (recv_buf)
        nn_freemsg(recv_buf);

    *timed_out = ftw_nanomsg_timeout(rc);

    return rc;
}

int ftw_nanomsg_ask(const int socket_id, const int send_timeout, const int recv_timeout,
    const LStrHandle request, LStrHandle response, LVBoolean *timed_out)
{
    int rc;
    struct nn_iovec iov;
    struct nn_msghdr hdr;
    void *recv_buf;
    MgErr resize_err;

    iov.iov_base = LHStrBuf(request);
    iov.iov_len = LHStrLen(request);

    hdr.msg_iov = &iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = NULL;
    hdr.msg_controllen = 0;
    
    rc = nn_setsockopt(socket_id, NN_SOL_SOCKET, NN_SNDTIMEO, &send_timeout, sizeof(send_timeout));
    if (rc < 0)
        return rc;

    rc = nn_setsockopt(socket_id, NN_SOL_SOCKET, NN_RCVTIMEO, &recv_timeout, sizeof(recv_timeout));
    if (rc < 0)
        return rc;

    rc = nn_sendmsg(socket_id, &hdr, 0);

    if (rc >= 0) {
        recv_buf = NULL;
        iov.iov_base = &recv_buf;
        iov.iov_len = NN_MSG;

        hdr.msg_iov = &iov;
        hdr.msg_iovlen = 1;
        hdr.msg_control = NULL;
        hdr.msg_controllen = 0;

        rc = nn_recvmsg(socket_id, &hdr, 0);

        if (rc >= 0) {
            resize_err = ftw_support_copy_to_LStrHandle(response, recv_buf, rc);
            if (resize_err != mgNoErr) {
                errno = resize_err + LV_USER_ERROR;
                rc = -1;
            }
        }

        if (recv_buf)
            nn_freemsg(recv_buf);
    }

    *timed_out = ftw_nanomsg_timeout(rc);

    return rc;
}

static void ftw_nanomsg_async_recv_thread(void *arg)
{
    struct ftw_socket *self;
    struct nn_iovec iov;
    struct nn_msghdr msg;
    struct lv_incoming_msg lv_msg;
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

        memset(&lv_msg, 0, sizeof(lv_msg));

        iov.iov_base = &lv_msg.msg;
        iov.iov_len = NN_MSG;

        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_control = &lv_msg.hdr;
        msg.msg_controllen = NN_MSG;

        rc = nn_recvmsg(self->id, &msg, 0);

        if (rc >= 0) {
            lv_msg.router_id = (uInt64)self;
            lv_msg.msg_len = (uInt64)nn_chunk_size((void *)lv_msg.msg);
            lv_msg.hdr_len = (uInt64)nn_chunk_size((void *)lv_msg.hdr);

            /*  On the LabVIEW side, the handler is a callback VI (rather than an Event
                Handler Structure). For this reason, this function is blocked for the
                duration of the callback, enabling LabVIEW to apply backpressure when
                the message queue is congested. This important semantic is desirable since
                that backpressure may be relayed all the way back to originating endpoints,
                synchronously relaying information about the remote's ability to handle
                messages it is sending. */
            lv_err = PostLVUserEvent(self->lv_event, &lv_msg);

        }
        else {
            socket_err = ((errno == EAGAIN) ? 0 : errno);
        }

        if (lv_msg.msg)
            nn_freemsg((void *)lv_msg.msg);

        if (lv_msg.hdr)
            nn_freemsg((void *)lv_msg.hdr);
    }

    /*  Thread will silently prune on error condition. */

    return;
}

int ftw_nanomsg_async_recv(struct ftw_socket *sock, LVUserEventRef *lv_event)
{
    int rc;

    rc = 0;

    return rc;
}

int ftw_nanomsg_router_start(struct ftw_socket_callsite **callsite, LVUserEventRef *lv_event, const char *addr, struct ftw_socket **router)
{
    struct ftw_socket *inst;
    int rcb;
    int rcs;

    rcs = nn_socket(AF_SP_RAW, NN_REP);

    /*  Socket creation failure? */
    if (rcs < 0)
        return rcs;

    rcb = ftw_nanomsg_bind(rcs, addr);

    /*  Endpoint creation failure? */
    if (rcb < 0) {
        ftw_nanomsg_close(rcs);
        *router = NULL;
        return rcb;
    }

    inst = nn_alloc(sizeof(struct ftw_socket), "ftw_socket");
    alloc_assert(inst);

    inst->lv_event = *lv_event;
    inst->id = rcs;
    inst->callsite = *callsite;

    nn_list_item_init(&inst->item);
    nn_list_insert(&(*callsite)->active_sockets, &inst->item,
        nn_list_end(&(*callsite)->active_sockets));

    /*  Launch thread and wait for it to initialize. */
    nn_sem_init(&inst->init_sem);
    nn_thread_init(&inst->thread, ftw_nanomsg_async_recv_thread, inst);
    nn_sem_wait(&inst->init_sem);

    *router = inst;

    return 0;
}

int ftw_nanomsg_router_reply(const struct ftw_socket * const router, const int timeout,
    const LStrHandle backtrace, const LStrHandle response, LVBoolean *timed_out)
{
    int rc;
    struct nn_iovec iov;
    struct nn_msghdr hdr;

    if (router == NULL) {
        errno = EBADF;
        return -1;
    }

    iov.iov_base = LHStrBuf(response);
    iov.iov_len = LHStrLen(response);

    hdr.msg_iov = &iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = LHStrBuf(backtrace);
    hdr.msg_controllen = LHStrLen(backtrace);

    rc = nn_setsockopt(router->id, NN_SOL_SOCKET, NN_SNDTIMEO, &timeout, sizeof(timeout));

    if (rc < 0)
        return rc;

    rc = nn_sendmsg(router->id, &hdr, 0);

    *timed_out = ftw_nanomsg_timeout(rc);

    return rc;
}

int ftw_nanomsg_router_stop(struct ftw_socket *router)
{
    int rc;

    if (router == NULL) {
        errno = EBADF;
        return -1;
    }

    rc = nn_socket_term(router->id);
    if (rc < 0)
        return rc;

    nn_sem_term(&router->init_sem);
    nn_thread_term(&router->thread);

    rc = nn_close(router->id);
    if (rc < 0)
        return rc;

    nn_list_erase(&(router->callsite)->active_sockets, &router->item);

    nn_free(router);
    router = NULL;

    return rc;
}

int ftw_nanomsg_close(const int socket_id)
{
    /*  It is safe to call this function repeatedly; however, subsequent calls
        on a socket that is already closed will return a benign error  */

    int rc;

    rc = nn_socket_term(socket_id);

    if (rc < 0)
        return rc;

    rc = nn_close(socket_id);

    return rc;
}

MgErr ftw_nanomsg_reserve(struct ftw_socket_callsite **inst)
{
    static int callsite = 0;

    /*  Creates a list of socket instances for each CLFN callsite. */
    if (*inst == NULL) {
        callsite++;
        *inst = nn_alloc(sizeof(struct ftw_socket_callsite), "callsite_socket_list");
        alloc_assert(*inst);
        nn_mutex_init(&(*inst)->sync);
        nn_mutex_lock(&(*inst)->sync);
        nn_list_init(&(*inst)->active_sockets);
        nn_mutex_unlock(&(*inst)->sync);
    }
    else {
        ftw_assert_impossible("Reserve happened twice. What's up with that?");
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
        ftw_debug("Unreserving: 0x%08x", *inst);
        nn_free(*inst);
        *inst = NULL;
    }
    else {
        ftw_debug("No-op unreserve: 0x%08x", *inst);
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
    int clean;
    int unclean;

    nn_mutex_lock(&callsite->sync);

    clean = 0;
    unclean = 0;

    while (!nn_list_empty(&callsite->active_sockets)) {
        it = nn_list_erase(&callsite->active_sockets, nn_list_begin(&callsite->active_sockets));
        if (!it)
            continue;
        sock = nn_cont(it, struct ftw_socket, item);
        ftw_debug("Cleaning up socket: %04d", sock->id);
        if (nn_socket_term(sock->id) == 0) {
            clean++;
        }
        else {
            unclean++;
        }
    }

    nn_list_term(&callsite->active_sockets);

    nn_mutex_unlock(&callsite->sync);

    ftw_debug("Terminated %d sockets cleanly, %d sockets uncleanly.", clean, unclean);

    return;
}