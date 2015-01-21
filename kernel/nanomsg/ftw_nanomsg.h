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

#ifndef FTW_NANOMSG_H_INCLUDED
#define FTW_NANOMSG_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "../ftw.h"
#include "upstream/src/utils/thread.h"
#include "upstream/src/nn.h"
#include "upstream/src/utils/err.h"
#include "upstream/src/utils/sem.h"
#include "upstream/src/utils/list.h"
#include "upstream/src/utils/mutex.h"

#define ftw_nanomsg_timeout(rc) ((rc < 0 && (errno == EAGAIN || errno == ETIMEDOUT)) ? LVBooleanTrue : LVBooleanFalse)

#define NN_INVALID_SOCKET_ID -1

/*  InstanceDataPtr types for nanomsg sockets. The list keeps up with all active
    sockets created per each callsite. This bookkeeping ensures each socket created
    is properly terminated and deallocated when a LabVIEW VI is aborted or finishes
    executing without explicitly closing the socket. */
struct ftw_socket_callsite {

    /*  Callsite ID assigned by LabVIEW CLFN. */
    int id;

    /*  List of sockets created by this callsite. */
    struct nn_list active_sockets;

    /*  Protect manipulation of active socket list across threads. */
    struct nn_mutex sync;
};


/*  Opaque type for socket bookkeeping. */
struct ftw_socket {

    /*  Socket ID assigned by nanomsg. */
    int id;

    /*  Callsite ID assigned by LabVIEW CLFN. */
    struct ftw_socket_callsite *callsite;

    /*  Parameters used for sockets with asynchronous receive. */
    LVUserEventRef lv_event;
    struct nn_sem init_sem;
    struct nn_thread thread;

    /*  This is just used by the List API to maintain position of this item. */
    struct nn_list_item item;
};

/*  Use LabVIEW-safe types for PostLVUserEvent. Use 64-bit, even in 32-bit environments. */
struct lv_incoming_msg {
    uInt64 router_id;
    uInt64 msg_len;
    uInt64 msg;
    uInt64 hdr_len;
    uInt64 hdr;
};

/*  Callbacks invoked by LabVIEW by individual instances of Call Library Function Nodes. */
FTW_EXPORT MgErr ftw_nanomsg_reserve(struct ftw_socket_callsite **inst);
FTW_EXPORT MgErr ftw_nanomsg_unreserve(struct ftw_socket_callsite **inst);
FTW_EXPORT MgErr ftw_nanomsg_abort(struct ftw_socket_callsite **inst);

/*  nanomsg library support methods. */
FTW_EXPORT int ftw_nanomsg_error(LStrHandle error_message);
FTW_EXPORT const char *ftw_nanomsg_version(void);

/*  Socket, endpoint, and connection methods. */
FTW_EXPORT int ftw_nanomsg_socket(struct ftw_socket_callsite **callsite, const int scalability_protocol,
    const LVBoolean *raw, const int linger, const int sndbuf, const int rcvbuf);
FTW_EXPORT int ftw_nanomsg_setsockopt(const int socket_id, int level, int option,
    const void *value, size_t length);
FTW_EXPORT int ftw_nanomsg_connect(const int socket_id, const char *addr);
FTW_EXPORT int ftw_nanomsg_bind(const int socket_id, const char *addr);
FTW_EXPORT int ftw_nanomsg_close(const int socket_id);

/*  Blocking I/O methods. */
FTW_EXPORT int ftw_nanomsg_send(const int socket_id, const int timeout,
    const LStrHandle outgoing_msg, LVBoolean *timed_out);
FTW_EXPORT int ftw_nanomsg_recv(const int socket_id, const int timeout,
    LStrHandle incoming_msg, LVBoolean *timed_out);
FTW_EXPORT int ftw_nanomsg_ask(const int socket_id, const int send_timeout,
    const int recv_timeout, const LStrHandle request, LStrHandle response, LVBoolean *timed_out);
FTW_EXPORT int ftw_nanomsg_async_recv(struct ftw_socket *sock, LVUserEventRef *lv_event);

/*  FTW Actor Message Router framework. */
FTW_EXPORT int ftw_nanomsg_router_start(struct ftw_socket_callsite **callsite, LVUserEventRef *lv_event,
    const char *addr, struct ftw_socket **router);
FTW_EXPORT int ftw_nanomsg_router_reply(const struct ftw_socket * const router, const int timeout,
    const LStrHandle backtrace, const LStrHandle response, LVBoolean *timed_out);
FTW_EXPORT int ftw_nanomsg_router_stop(struct ftw_socket *router);

#ifdef __cplusplus
}
#endif

#endif
