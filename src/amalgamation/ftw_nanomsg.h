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

#ifndef FTW_H_INCLUDED
#define FTW_H_INCLUDED
#define NN_NO_EXPORTS

#ifdef __cplusplus
extern "C" {
#endif

/* This is in the LabVIEW directory */
//#include <extcode.h>
#include "utils/thread.h"
#include "nn.h"

#if   defined _WIN32
#     define FTW_EXPORT __declspec(dllexport)
#elif defined __SUNPRO_C
#     define FTW_EXPORT __global
#elif (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER || defined __clang__
#     define FTW_EXPORT __attribute__ ((visibility("default")))
#else
#     define FTW_EXPORT
#endif

//typedef struct {
//	int frontend;
//	int backend;
//} ftw_nanomsg_router_worker_inputs;

FTW_EXPORT const char *ftw_nanomsg_error (int *error_code);
FTW_EXPORT const char *ftw_nanomsg_version (void);
FTW_EXPORT int ftw_nanomsg_send (int s, const void *buf, size_t length, int timeout, int flags);
FTW_EXPORT int ftw_nanomsg_recv (int s, void *buf, size_t length, int timeout, int flags);
FTW_EXPORT int ftw_nanomsg_connect (int s, const char *addr);
FTW_EXPORT int ftw_nanomsg_bind (int s, const char *addr);
FTW_EXPORT int ftw_nanomsg_close (int s);

FTW_EXPORT int ftw_nanomsg_router_start (const char *addr);
FTW_EXPORT int ftw_nanomsg_router_recv (int router_id, void *incoming_msg_body, size_t *incoming_body_size, void *incoming_msg_header, size_t *incoming_header_size, int timeout);
FTW_EXPORT int ftw_nanomsg_router_stop (int router_id);

#ifdef __cplusplus
}
#endif

#endif