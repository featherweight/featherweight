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

#include "ftw.h"
#include <string.h>

void *ftw_malloc(size_t sz)
{
    return DSNewPtr(sz);
}

ftwrc ftw_free(void *ptr)
{
    MgErr lvrc;

    lvrc = DSDisposePtr(ptr);

    return (lvrc ? lvrc + ELVMGRBASE : EFTWOK);
}

char *ftw_support_LStrHandle_to_CStr(LStrHandle src)
{
    char *s;
    size_t len;

    if (src == NULL) {
        return NULL;
    }

    len = LHStrLen(src);

    s = ftw_malloc(len + 1);
    if (s == NULL) {
        return NULL;
    }

    MoveBlock(LHStrBuf(src), s, len);
    s[len] = '\0';

    return s;
}

ftwrc ftw_support_buffer_to_LStrHandle(LStrHandle *dest, const void *src, size_t length, size_t offset)
{
    MgErr lvrc;
    size_t sz;

    if (src == NULL) {
        return EFTWARG;
    }

    lvrc = NumericArrayResize(uB, 1, (UHandle *)dest, length + offset);
    if (lvrc != mgNoErr) {
        return ELVMGRBASE + lvrc;
    }

    ftw_assert(dest && *dest);
    sz = DSGetHandleSize(*dest);
    ftw_assert(sz == length + offset + sizeof(int32));
    MoveBlock(src, LHStrBuf(*dest) + offset, length);
    (**dest)->cnt = (int32) (length + offset);

    return EFTWOK;
}

ftwrc ftw_support_CStr_to_LStrHandle(LStrHandle *dest, const char *src, size_t max_length)
{
    ftwrc rc;
    size_t len;

    if (src == NULL) {
        return EFTWARG;
    }

    len = strnlen(src, max_length);
    rc = ftw_support_buffer_to_LStrHandle(dest, src, len, 0);

    return rc;
}

ftwrc ftw_support_expand_LStrHandleArray(LStrHandleArray ***arr, size_t elements)
{
    MgErr lvrc;

    if (arr == NULL || *arr == NULL || **arr == NULL) {
        return EFTWARG;
    }

    lvrc = NumericArrayResize(uL, 1, (UHandle *)arr, elements);
    if (lvrc != mgNoErr) {
        return ELVMGRBASE + lvrc;
    }
    
    (**arr)->dimsize = (int32)elements;

    return EFTWOK;
}

ftwrc ftw_support_expand_PointerArray(PointerArray ***arr, size_t elements)
{
    MgErr lvrc;
    int32 sz;

    if (arr == NULL || *arr == NULL || **arr == NULL) {
        return EFTWARG;
    }

    FTW_COMPILER_ASSERT(sizeof(void*) == 8 || sizeof(void*) == 4);
    
    switch (sizeof(void*)) {
    case 8:
        sz = uQ;
        break;
    case 4:
        sz = uL;
        break;
    default:
        ftw_assert_unreachable("Compiler assertion failed.");
    }

    lvrc = NumericArrayResize(sz, 1, (UHandle *)arr, elements);
    if (lvrc != mgNoErr) {
        return ELVMGRBASE + lvrc;
    }

    (**arr)->dimsize = (int32)elements;

    return EFTWOK;
}

ftwrc ftw_support_expand_int32Array(int32Array ***arr, size_t elements)
{
    MgErr lvrc;

    if (arr == NULL || *arr == NULL || **arr == NULL) {
        return EFTWARG;
    }

    lvrc = NumericArrayResize(uL, 1, (UHandle *)arr, elements);
    if (lvrc != mgNoErr) {
        return ELVMGRBASE + lvrc;
    }

    (**arr)->dimsize = (int32)elements;

    return EFTWOK;
}
