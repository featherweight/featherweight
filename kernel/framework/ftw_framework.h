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

#ifndef FTW_FRAMEWORK_H_INCLUDED
#define FTW_FRAMEWORK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "../ftw.h"
#include "../jansson/ftw_json.h"
#include "../nanomsg/ftw_nanomsg.h"
#include "../pcre/ftw_pcre.h"
#include "../ftw_libuv.h"

    /*  Actual structure of an incoming request to an Inbox; packaged as an opaque pointer for LabVIEW. */
    struct ftw_incoming_request {
        struct ftw_socket_inbox *inbox;
        void *msg_ptr;
        size_t msg_len;
        void *hdr_ptr;
        size_t hdr_len;
    };

    /*  Finite states of the FTW Inbox. */
    typedef enum {UNINITIALIZED, ACTIVE, ZOMBIFIED} ftw_inbox_state;

    /*  Actual structure of an incoming request to an Inbox; packaged as an opaque pointer for LabVIEW. */
    struct ftw_socket_inbox {

        /*  Socket ID assigned by nanomsg. */
        int id;

        /*  Object lifetime management. */
        ftw_inbox_state state;
        uv_mutex_t lock;

        /*  Asynchronous receive parameters. */
        LVUserEventRef incoming_msg_notifier_event;
        uv_thread_t async_recv_thread;
        uv_sem_t initialized;
        uv_sem_t deinitialized;
        uv_sem_t msg_acknowledged;
    };


/*  FTW Actor Inbox framework. */
FTW_EXPORT ftwrc ftw_actor_inbox_construct(struct ftw_socket_inbox **inst, LVUserEventRef *msg_to_lv_event,
    struct ftw_socket_inbox **sock, const LStrHandleArray **addresses, int max_recv_size);
FTW_EXPORT ftwrc ftw_actor_inbox_recv(struct ftw_incoming_request *incoming, json_t **json_msg, size_t flags,
    int64 *err_line, int64 *err_column, int64 *err_position, LStrHandle err_source, LStrHandle err_hint);
FTW_EXPORT ftwrc ftw_actor_inbox_reply(json_t *response, struct ftw_incoming_request *req, const int timeout);
FTW_EXPORT ftwrc ftw_actor_inbox_shutdown(struct ftw_socket_inbox ** const sock);

/*  FTW Actor Inbox Message Router callbacks. */
FTW_EXPORT MgErr ftw_actor_inbox_reserve(struct ftw_socket_inbox **inst);
FTW_EXPORT MgErr ftw_actor_inbox_unreserve(struct ftw_socket_inbox **inst);
FTW_EXPORT MgErr ftw_actor_inbox_abort(struct ftw_socket_inbox **inst);

/*  Featherweight exported functions. */
FTW_EXPORT const char *ftw_version(void);
FTW_EXPORT void ftw_resource_usage(double *user_cpu_time, double *system_cpu_time, double *uptime, uint64_t *hi_res_relative_time,
    uint64_t *peak_working_set, uint64_t *lv_dataspace_size, uint64_t *hard_page_faults);

#ifdef __cplusplus
}
#endif

#endif