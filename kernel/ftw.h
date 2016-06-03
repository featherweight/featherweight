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

#ifndef FTW_H_INCLUDED
#define FTW_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <math.h>

#include "extcode.h"

#define FTW_DEBUG_WINDOW 0
#define LV_USER_ERROR 5000

#define FTW_NaN NAN

/*  Featherweight export declarations. */
#if defined _WIN32
    #define FTW_EXPORT __declspec(dllexport)
#elif (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER || defined __clang__
    #define FTW_EXPORT __attribute__ ((visibility("default")))
#else
    #error
#endif

/*  Performance optimization for inlining functions. */
#ifdef __cplusplus
    #define FTW_INLINE inline
#else
    #define FTW_INLINE __inline
#endif
#define FTW_PRIVATE_SUPPORT static FTW_INLINE

/*  Featherweight support macros. */
#if FTW_DEBUG_WINDOW
    #define ftw_debug(fmt,...) DbgPrintf(fmt,__VA_ARGS__)
#else
    #define ftw_debug(fmt,...)
#endif

/*  Run-time assert (adopted from nanomsg). */
#define ftw_assert(x) \
    do {\
        if (!(x)) {\
            fprintf (stderr, "Assertion failed: %s (%s:%d)\n", #x, \
                __FILE__, __LINE__);\
            fflush (stderr);\
            abort ();\
                }\
        } while (0)
#define ftw_assert_unreachable(s) \
    do {\
            fprintf (stderr, "This should never happen! Here's why: %s (%s:%d)\n", #s, \
                __FILE__, __LINE__);\
            fflush (stderr);\
            abort ();\
       } while (0)

/*  Compile-time assert (adopted from nanomsg). */
#define FTW_CTASSERT_2(prefix, line) prefix##line
#define FTW_CTASSERT_1(prefix, line) FTW_CTASSERT_2(prefix, line)
#if defined __COUNTER__
#define FTW_COMPILER_ASSERT(x) \
    typedef int FTW_CTASSERT_1(ct_assert_,__COUNTER__) [(x) ? 1 : -1]
#else
#define CT_ASSERT(x) \
    typedef int FTW_CTASSERT_1(ct_assert_,__LINE__) [(x) ? 1 : -1]
#endif

/*  Featherweight support types. */
typedef struct {
    int32 dimsize;
    LStrHandle element[1];
} LStrHandleArray;

typedef struct {
    int32 dimsize;
    intptr_t element[1];
} PointerArray;

typedef struct {
    int32 dimsize;
    int32 element[1];
} int32Array;

/*  Featherweight support functions. */
char * ftw_support_LStrHandle_to_CStr(LStrHandle src);
MgErr ftw_support_buffer_to_LStrHandle(LStrHandle *dest, const void *src, size_t length);
MgErr ftw_support_CStr_to_LStrHandle(LStrHandle *dest, const char *src, size_t max_length);
MgErr ftw_support_expand_LStrHandleArray(LStrHandleArray ***arr, size_t elements);
MgErr ftw_support_expand_PointerArray(PointerArray ***arr, size_t elements);
MgErr ftw_support_expand_int32Array(int32Array ***arr, size_t elements);
#define ftw_recover_LStrHandle(ptr) (ptr ? (LStrHandle)DSRecoverHandle(ptr - Offset(LStr, str[0])) : NULL)

#ifdef __cplusplus
}
#endif

#endif
