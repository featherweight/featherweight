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

#ifndef FTW_NANOMSG_H_INCLUDED
#define FTW_NANOMSG_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "../ftw.h"
    
#include "upstream/src/nn.h"
#include "upstream/src/reqrep.h"
#include "upstream/src/utils/chunk.h"
#include "upstream/src/utils/cont.h"
#include "upstream/src/utils/err.h"
#include "upstream/src/utils/sem.h"
#include "upstream/src/utils/list.h"
#include "upstream/src/utils/mutex.h"
#include "upstream/src/utils/thread.h"

/*  InstanceDataPtr types for nanomsg sockets. The list keeps up with all active
    sockets created per each callsite. This bookkeeping ensures each socket created
    is properly terminated and deallocated when a LabVIEW VI is aborted or finishes
    executing without explicitly closing the socket. */
struct ftw_socket_callsite {

    /*  Callsite ID assigned by FTW. */
    int id;

    /*  List of sockets created by this callsite. */
    struct nn_list active_sockets;

    /*  Protect manipulation of active socket list across threads. */
    struct nn_mutex sync;

    /*  Total number of lifetime sockets created. */
    int lifetime_sockets;
};

/*  Opaque type for socket bookkeeping. */
struct ftw_socket {

    /*  Socket ID assigned by nanomsg. */
    int id;

    /*  Callsite ID on reserve of LabVIEW CLFN. */
    struct ftw_socket_callsite *callsite;

    /*  Asynchronous receive parameters. */
    LVUserEventRef incoming_msg_notifier_event;
    struct nn_thread async_recv_thread;
    struct nn_sem async_recv_ready;

    /*  This is just used by the List API to maintain position of this item. */
    struct nn_list_item item;
};

/*  Callbacks invoked by LabVIEW by individual instances of Call Library Function Nodes. */
FTW_EXPORT MgErr ftw_nanomsg_reserve(struct ftw_socket_callsite **inst);
FTW_EXPORT MgErr ftw_nanomsg_unreserve(struct ftw_socket_callsite **inst);
FTW_EXPORT MgErr ftw_nanomsg_abort(struct ftw_socket_callsite **inst);

/*  nanomsg library support methods. */
FTW_EXPORT void ftw_nanomsg_error(LStrHandle error_message, int64 *code);

/*  FTW Actor Connector framework. */
FTW_EXPORT ftwrc ftw_actor_connector_connect(struct ftw_socket_callsite **callsite, const char *addr,
    int max_recv_size, struct ftw_socket **sock);
FTW_EXPORT ftwrc ftw_actor_connector_ask(struct ftw_socket ** const sock, int send_timeout,
    int recv_timeout, const LStrHandle request, LStrHandle response);
FTW_EXPORT ftwrc ftw_actor_connector_disconnect(struct ftw_socket ** const sock);

/*  FTW Publisher framework. */
FTW_EXPORT ftwrc ftw_publisher_construct(struct ftw_socket_callsite **callsite, const char *addr,
    struct ftw_socket **sock);
FTW_EXPORT ftwrc ftw_publisher_publish(struct ftw_socket ** const sock, int send_timeout, ConstLStrH message);
FTW_EXPORT ftwrc ftw_publisher_destroy(struct ftw_socket ** const sock);

/*  FTW Subscriber framework. */
FTW_EXPORT ftwrc ftw_subscriber_construct(struct ftw_socket_callsite **callsite, LVUserEventRef *lv_event,
    const char *addr, int linger, int max_recv_size, struct ftw_socket **sock);
FTW_EXPORT ftwrc ftw_subscriber_destroy(struct ftw_socket ** const sock);

#ifdef __cplusplus
}
#endif

#endif
