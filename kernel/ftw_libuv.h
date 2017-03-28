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

#ifndef FTW_LIBUV_H_INCLUDED
#define FTW_LIBUV_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "ftw.h"

#ifndef ssize_t
#define ssize_t intptr_t
#endif
#ifndef _SSIZE_T_DEFINED
#define _SSIZE_T_DEFINED
#endif

#include "libuv/include/uv.h"

/*  InstanceDataPtr types for libuv callsites that create an event loop. */
struct ftw_libuv_callsite {

    /*  Callsite ID assigned by FTW. */
    int id;

    /*  Event Loop instance for this callsite. */
    uv_loop_t *loop_instance;
};

struct ftw_libuv_process {
    int64_t *exit_code;
    int64_t *signal;
};

/*  Asynchronous streams into LabVIEW. */
struct ftw_libuv_stream {
    LVUserEventRef *msg_to_lv_event;
};

#include "lv_prolog.h"
struct ftw_libuv_stream_output {
    LStrHandle output;
    int64 code;
};
#include "lv_epilog.h"

/*  Callbacks invoked by LabVIEW by individual instances of Call Library Function Nodes. */
FTW_EXPORT MgErr ftw_libuv_reserve(struct ftw_libuv_callsite **inst);
FTW_EXPORT MgErr ftw_libuv_unreserve(struct ftw_libuv_callsite **inst);
FTW_EXPORT MgErr ftw_libuv_abort(struct ftw_libuv_callsite **inst);

FTW_EXPORT void ftw_libuv_error(int *err_number, LStrHandle error_name, LStrHandle error_message);
FTW_EXPORT ftwrc ftw_libuv_version(LStrHandle version);
FTW_EXPORT ftwrc ftw_libuv_lib_path(LStrHandle path);
FTW_EXPORT void ftw_high_resolution_time(uint64_t *nanoseconds);

FTW_EXPORT int ftw_libuv_spawn_process(struct ftw_libuv_callsite **callsite, LVUserEventRef *lv_event,
    char *exe, char *cmd, int64_t *exit_code, int64_t *signal);

#ifdef __cplusplus
}
#endif

#endif
