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

#ifndef FTW_H_INCLUDED
#define FTW_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#include "labview/extcode.h"

#define FTW_DEBUG_WINDOW 0
#define LV_USER_ERROR 5000

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

#define ftw_assert(x) \
    do {\
        if (!(x)) {\
            fprintf (stderr, "Assertion failed: %s (%s:%d)\n", #x, \
                __FILE__, __LINE__);\
            fflush (stderr);\
            abort ();\
                }\
        } while (0)
#define ftw_assert_impossible(s) \
    do {\
            fprintf (stderr, "This should never happen! Here's why: %s (%s:%d)\n", #s, \
                __FILE__, __LINE__);\
            fflush (stderr);\
            abort ();\
            } while (0)

/*  IEEE 754 macros for checking NaN and Inf (from value.c in Jansson). */
#ifndef isnan
    FTW_PRIVATE_SUPPORT int isnan(double x) { return x != x; }
#endif
#ifndef isinf
    FTW_PRIVATE_SUPPORT int isinf(double x) { return !isnan(x) && isnan(x - x); }
#endif

/*  Featherweight support types. */
typedef struct {
    int32 dimsize;
    LStrHandle element[1];
} LStrHandleArray;

typedef struct {
    int32 dimsize;
    int32 element[1];
} I32Array;

typedef struct {
    int32 dimsize;
    intptr_t element[1];
} PointerArray;

#define ftw_support_sizeof_array(arr_type,len) Offset(arr_type, element) + sizeof(arr_type) * len

/*  Featherweight support functions. */
MgErr ftw_support_buffer_to_LStrHandle(LStrHandle *dest, const void *src, size_t length);
MgErr ftw_support_CStr_to_LStrHandle(LStrHandle *dest, const char *src);
MgErr ftw_support_resize_PointerArray(PointerArray **arr, size_t elements);
MgErr ftw_support_resize_LStrHandleArray(LStrHandleArray **arr, size_t elements);

#ifdef __cplusplus
}
#endif

#endif
