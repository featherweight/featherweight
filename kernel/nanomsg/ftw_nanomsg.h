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

#define LV_USER_ERROR 5000

#define ftw_nanomsg_timeout(rc) ((rc < 0 && (errno == EAGAIN || errno == ETIMEDOUT)) ? LVBooleanTrue : LVBooleanFalse)

#define NN_INVALID_SOCKET_ID -1
#define ftw_nanomsg_instance_set(inst, inst_id) ((*(*inst))->id = inst_id)
#define ftw_nanomsg_instance_is_valid(inst) ((*(*inst))->id != NN_INVALID_SOCKET_ID)

	/*  InstanceDataPtr types for nanomsg sockets. */
	typedef struct {
		int id;
    } SocketInstance;

    /*  Router thread arguments. */
    struct ftw_router_args {
        int router_id;
        LVUserEventRef lv_event;
        struct nn_sem initialized;
        SocketInstance **inst;
    };

    /*  Use LabVIEW-safe types. */
    struct lv_incoming_msg {
        uInt64 router_id;
        uInt64 msg_len;
        uInt64 msg;
        uInt64 hdr_len;
        uInt64 hdr;
    };

	/*  Callbacks invoked by LabVIEW by individual instances of Call Library Function Nodes  */
    FTW_EXPORT MgErr ftw_nanomsg_reserve(SocketInstance ***inst);
    FTW_EXPORT MgErr ftw_nanomsg_unreserve(SocketInstance ***inst);
    FTW_EXPORT MgErr ftw_nanomsg_abort(SocketInstance ***inst);

	/*  nanomsg library support methods  */
	FTW_EXPORT int ftw_nanomsg_error(LStrHandle error_message);
	FTW_EXPORT const char *ftw_nanomsg_version(void);

	/*  Socket, endpoint, and connection methods  */
    FTW_EXPORT int ftw_nanomsg_socket(SocketInstance ***inst, const int scalability_protocol,
        const LVBoolean *raw, const int linger, const int sndbuf, const int rcvbuf);
	FTW_EXPORT int ftw_nanomsg_connect(const int socket_id, const char *addr);
	FTW_EXPORT int ftw_nanomsg_bind(const int socket_id, const char *addr);
	FTW_EXPORT int ftw_nanomsg_close(const int socket_id);

	/*  Blocking I/O methods  */
    FTW_EXPORT int ftw_nanomsg_send(SocketInstance ***inst, const int socket_id, const int timeout,
        const LStrHandle outgoing_msg, LVBoolean *timed_out);
    FTW_EXPORT int ftw_nanomsg_recv(SocketInstance ***inst, const int socket_id, const int timeout,
        LStrHandle incoming_msg, LVBoolean *timed_out);
    FTW_EXPORT int ftw_nanomsg_ask(SocketInstance ***inst, const int socket_id, const int send_timeout,
        const int recv_timeout, const LStrHandle request, LStrHandle response, LVBoolean *timed_out);

	/*  FTW Actor Message Router framework  */
    FTW_EXPORT int ftw_nanomsg_router_start(SocketInstance ***inst, LVUserEventRef *lv_event, const char *addr);
    FTW_EXPORT int ftw_nanomsg_router_recv(SocketInstance ***inst, const int router_id, const int timeout,
        LStrHandle backtrace, LStrHandle incoming_request, LVBoolean *message_received, LVBoolean *shutdown, LVUserEventRef *lv_event);
    FTW_EXPORT int ftw_nanomsg_router_reply(SocketInstance ***inst, const int router_id, const int timeout,
        const LStrHandle backtrace, const LStrHandle response, LVBoolean *timed_out);
	FTW_EXPORT int ftw_nanomsg_router_stop(const int router_id);

#ifdef __cplusplus
}
#endif

#endif
