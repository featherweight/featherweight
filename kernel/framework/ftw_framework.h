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

#ifndef FTW_FRAMEWORK_H_INCLUDED
#define FTW_FRAMEWORK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "../ftw.h"
#include "../jansson/ftw_json.h"
#include "../nanomsg/ftw_nanomsg.h"
#include "../pcre/ftw_pcre.h"
//#include "../sqlite/ftw_sqlite.h"

/*  Actual structure of an incoming request to an Inbox; packaged as an opaque pointer for LabVIEW. */
    struct ftw_incoming_request {
        struct ftw_socket *sock;
        void *msg_ptr;
        size_t msg_len;
        void *hdr_ptr;
        size_t hdr_len;
    };

/*  FTW Actor Inbox framework. */
FTW_EXPORT int ftw_framework_inbox_start(struct ftw_socket_callsite **callsite, LVUserEventRef *lv_event,
    const LStrHandleArray **addresses, int linger, int max_recv_size, struct ftw_socket **sock);
FTW_EXPORT json_t *ftw_framework_inbox_recv(struct ftw_incoming_request *incoming, size_t flags, int64 *err_line,
    int64 *err_column, int64 *err_position, LStrHandle err_source, LStrHandle err_hint);
FTW_EXPORT int ftw_framework_inbox_reply(json_t *response, struct ftw_incoming_request *req, const int timeout);

/*  Featherweight exported functions. */
FTW_EXPORT const char *ftw_version(void);
FTW_EXPORT void ftw_lvmem(int64 *ds_bytes_allocated);

#ifdef __cplusplus
}
#endif

#endif