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
#include "reqrep.h"
#include "pubsub.h"
#include "pipeline.h"
#include "survey.h"
#include "pair.h"
#include "bus.h"
#include <stdlib.h>

//#include "utils/sleep.h"
#include "utils/chunk.h"

static MgErr ftw_support_copy_to_LStrHandle(LStrHandle dest, const void *src, size_t length)
{
    MgErr resize_err;

    resize_err = NumericArrayResize(uB, 1, (UHandle *)&dest, length);
    if (resize_err == mgNoErr) {
        MoveBlock(src, LHStrBuf(dest), length);
        LStrLen(*dest) = length;
    }
    return resize_err;
}

int ftw_nanomsg_error(LStrHandle error_message)
{
    const char* human_readable_error;
    int current_error;

    current_error = errno;

    /*  The FTW library will explicitly handle a few errors, since "socket"
        could be a less misleading term than "file descriptors". */
    switch (current_error)
    {
    case EBADF:
        human_readable_error = "Invalid socket";
        break;
    case EMFILE:
        human_readable_error = "Too many open sockets";
        break;
    default:
        human_readable_error = nn_strerror(current_error);
    }

    ftw_support_copy_to_LStrHandle(error_message, human_readable_error, strlen(human_readable_error));

    return errno;
}

const char *ftw_nanomsg_version(void)
{
    return "0.5.0-1004";
}

int ftw_nanomsg_socket(SocketInstanceDataPtr *inst, const int scalability_protocol,
    const LVBoolean *raw, const int linger, const int sndbuf, const int rcvbuf)
{
    int socket_id;
    int domain;
    int protocol;

    int available_protocols[10] = { NN_REP, NN_REQ, NN_PUB, NN_SUB, NN_PUSH, NN_PULL, NN_SURVEYOR, NN_RESPONDENT, NN_PAIR, NN_BUS };

    ftw_assert(*inst);

    if (scalability_protocol < 0 || scalability_protocol >= sizeof(available_protocols) / sizeof(available_protocols[0]))
    {
        errno = EINVAL;
        return -1;
    }

    domain = (*raw == LVBooleanFalse) ? AF_SP : AF_SP_RAW;
    protocol = available_protocols[scalability_protocol];

    socket_id = nn_socket(domain, protocol);

    if (socket_id >= 0)
    {
        if (nn_setsockopt(socket_id, NN_SOL_SOCKET, NN_LINGER, &linger, sizeof(linger)) < 0)
            return -1;
        if (nn_setsockopt(socket_id, NN_SOL_SOCKET, NN_SNDBUF, &sndbuf, sizeof(sndbuf)) < 0)
            return -1;
        if (nn_setsockopt(socket_id, NN_SOL_SOCKET, NN_RCVBUF, &rcvbuf, sizeof(rcvbuf)) < 0)
            return -1;
    }

    return socket_id;
}

int ftw_nanomsg_connect(const int socket_id, const char *addr)
{
    int connection_id;

    connection_id = nn_connect(socket_id, addr);

    return connection_id;
}

int ftw_nanomsg_bind(const int socket_id, const char *addr)
{
    int binding_id;

    binding_id = nn_bind(socket_id, addr);

    return binding_id;
}

int ftw_nanomsg_send(SocketInstanceDataPtr *inst, const int socket_id, const int timeout,
    const LStrHandle outgoing_msg, LVBoolean *timed_out)
{
    int rc;
    struct nn_iovec iov;
    struct nn_msghdr hdr;

    ftw_assert(*inst);

    iov.iov_base = LHStrBuf(outgoing_msg);
    iov.iov_len = LHStrLen(outgoing_msg);

    memset(&hdr, 0, sizeof(hdr));
    hdr.msg_iov = &iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = NULL;
    hdr.msg_controllen = 0;

    nn_setsockopt(socket_id, NN_SOL_SOCKET, NN_SNDTIMEO, &timeout, sizeof(timeout));

    /*  Prepare LabVIEW Execution System for blocking call, in case abort() is called  */
    ftw_nanomsg_instance_set(inst, socket_id);
    rc = nn_sendmsg(socket_id, &hdr, 0);
    ftw_nanomsg_instance_set(inst, NN_INVALID_SOCKET_ID);

    *timed_out = ftw_nanomsg_timeout(rc);

    return rc;
}

int ftw_nanomsg_recv(SocketInstanceDataPtr *inst, const int socket_id, const int timeout,
    LStrHandle incoming_msg, LVBoolean *timed_out)
{
    int rc;
    struct nn_iovec iov;
    struct nn_msghdr hdr;
    void *recv_buf;
    MgErr resize_err;

    ftw_assert(*inst);

    recv_buf = NULL;
    iov.iov_base = &recv_buf;
    iov.iov_len = NN_MSG;

    memset(&hdr, 0, sizeof(hdr));
    hdr.msg_iov = &iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = NULL;
    hdr.msg_controllen = 0;

    nn_setsockopt(socket_id, NN_SOL_SOCKET, NN_RCVTIMEO, &timeout, sizeof(timeout));

    /*  Prepare LabVIEW Execution System for blocking call, in case abort() is called  */
    ftw_nanomsg_instance_set(inst, socket_id);
    rc = nn_recvmsg(socket_id, &hdr, 0);
    ftw_nanomsg_instance_set(inst, NN_INVALID_SOCKET_ID);

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

int ftw_nanomsg_ask(SocketInstanceDataPtr *inst, const int socket_id, const int send_timeout,
    const int recv_timeout, const LStrHandle request, LStrHandle response, LVBoolean *timed_out)
{
    int rc;
    struct nn_iovec iov;
    struct nn_msghdr hdr;
    void *recv_buf;
    MgErr resize_err;

    ftw_assert(*inst);

    iov.iov_base = LHStrBuf(request);
    iov.iov_len = LHStrLen(request);

    hdr.msg_iov = &iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = NULL;
    hdr.msg_controllen = 0;

    nn_setsockopt(socket_id, NN_SOL_SOCKET, 1, &send_timeout, sizeof(send_timeout));

    /*  Prepare LabVIEW Execution System for blocking call, in case abort() is called  */
    ftw_nanomsg_instance_set(inst, socket_id);
    rc = nn_sendmsg(socket_id, &hdr, 0);
    ftw_nanomsg_instance_set(inst, NN_INVALID_SOCKET_ID);

    if (rc >= 0) {
        recv_buf = NULL;
        iov.iov_base = &recv_buf;
        iov.iov_len = NN_MSG;

        hdr.msg_iov = &iov;
        hdr.msg_iovlen = 1;
        hdr.msg_control = NULL;
        hdr.msg_controllen = 0;

        nn_setsockopt(socket_id, NN_SOL_SOCKET, NN_RCVTIMEO, &recv_timeout, sizeof(recv_timeout));

        /*  Prepare LabVIEW Execution System for blocking call, in case abort() is called  */
        ftw_nanomsg_instance_set(inst, socket_id);
        rc = nn_recvmsg(socket_id, &hdr, 0);
        ftw_nanomsg_instance_set(inst, NN_INVALID_SOCKET_ID);

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

int ftw_nanomsg_router_start(SocketInstanceDataPtr *inst, const char *addr)
{
    int router_id;

    ftw_assert(*inst && !ftw_nanomsg_instance_is_valid(inst));

    router_id = nn_socket(AF_SP_RAW, NN_REP);

    if (router_id >= 0) {
        if (ftw_nanomsg_bind(router_id, addr) >= 0) {
            //			ftw_nanomsg_set_instance(inst, router_id);
        }
        else {
            ftw_nanomsg_close(router_id);
            router_id = -1;
        }
    }

//    nn_sleep(200);

    return router_id;
}

int ftw_nanomsg_router_recv(SocketInstanceDataPtr *inst, const int router_id, const int timeout,
    LStrHandle backtrace, LStrHandle incoming_request, LVBoolean *message_received, LVBoolean *shutdown)
{
    struct nn_iovec iov;
    struct nn_msghdr msg;
    void *recv_buf;
    void *hdr_buf;
    size_t hdr_len;
    int msg_size;
    MgErr resize_err;

    ftw_assert(*inst);

    recv_buf = NULL;
    hdr_buf = NULL;
    iov.iov_base = &recv_buf;
    iov.iov_len = NN_MSG;

    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = &hdr_buf;
    msg.msg_controllen = NN_MSG;

    nn_setsockopt(router_id, NN_SOL_SOCKET, NN_RCVTIMEO, &timeout, sizeof(timeout));

    /*  Prepare LabVIEW Execution System for blocking call, in case abort() is called  */
    ftw_nanomsg_instance_set(inst, router_id);
    msg_size = nn_recvmsg(router_id, &msg, 0);
    ftw_nanomsg_instance_set(inst, NN_INVALID_SOCKET_ID);

    if (msg_size >= 0) {
        resize_err = ftw_support_copy_to_LStrHandle(incoming_request, recv_buf, msg_size);
        if (resize_err != mgNoErr) {
            errno = resize_err + LV_USER_ERROR;
            msg_size = -1;
        }

        hdr_len = nn_chunk_size(hdr_buf);

        resize_err = ftw_support_copy_to_LStrHandle(backtrace, hdr_buf, hdr_len);
        if (resize_err != mgNoErr) {
            errno = resize_err + LV_USER_ERROR;
            msg_size = -1;
        }

        *message_received = LVBooleanTrue;
    }

    if (recv_buf)
        nn_freemsg(recv_buf);
    if (hdr_buf)
        nn_freemsg(hdr_buf);

    /*  This is the expected shutdown condition  */
    if (msg_size < 0 || errno == -EINTR)
    {
        errno = 0;
        *shutdown = LVBooleanTrue;
        return 0;
    }

    return msg_size;
}

int ftw_nanomsg_router_reply(SocketInstanceDataPtr *inst, const int router_id, const int timeout,
    const LStrHandle backtrace, const LStrHandle response, LVBoolean *timed_out)
{
    int rc;
    struct nn_iovec iov;
    struct nn_msghdr hdr;

    ftw_assert(*inst);

    iov.iov_base = LHStrBuf(response);
    iov.iov_len = LHStrLen(response);

    hdr.msg_iov = &iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = LHStrBuf(backtrace);
    hdr.msg_controllen = LHStrLen(backtrace);

    nn_setsockopt(router_id, NN_SOL_SOCKET, NN_SNDTIMEO, &timeout, sizeof(timeout));

    /*  Prepare LabVIEW Execution System for blocking call, in case abort() is called  */
    ftw_nanomsg_instance_set(inst, router_id);
    rc = nn_sendmsg(router_id, &hdr, 0);
    ftw_nanomsg_instance_set(inst, NN_INVALID_SOCKET_ID);

    return rc;
}

int ftw_nanomsg_router_stop(const int router_id)
{
    return ftw_nanomsg_close(router_id);
}

int ftw_nanomsg_close(const int socket_id)
{
    /*  It is safe to call this function repeatedly; however, subsequent calls
        on a socket that is already closed will return a benign error  */
    return nn_close(socket_id);
}

MgErr ftw_nanomsg_reserve(SocketInstanceDataPtr *inst)
{
    if (!*inst)
        *inst = (SocketInstanceDataPtr)DSNewPClr(sizeof(SocketInstanceData));

    ftw_assert(*inst);

    ftw_nanomsg_instance_set(inst, NN_INVALID_SOCKET_ID);

    ftw_assert(!ftw_nanomsg_instance_is_valid(inst));

    return mgNoErr;
}

MgErr ftw_nanomsg_unreserve(SocketInstanceDataPtr *inst)
{
    ftw_assert(*inst);

    //JRD - Enabling the following line causes crashes, and I don't know why.
    //      For now, allow this tiny memory leak to exist (a few bytes per API method instance)
    //ftw_assert(DSDisposePtr(*inst) == mgNoErr);

    return mgNoErr;
}

MgErr ftw_nanomsg_abort(SocketInstanceDataPtr *inst)
{
    if (ftw_nanomsg_instance_is_valid(inst))
    {
        ftw_nanomsg_close((*inst)->id);
        ftw_nanomsg_instance_set(inst, NN_INVALID_SOCKET_ID);
    }

    return mgNoErr;
}