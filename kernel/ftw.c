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

#include "ftw.h"
#include <string.h>

char * ftw_support_LStrHandle_to_CStr(LStrHandle src)
{
    char *s;
    size_t len;

    if (src == NULL)
        return NULL;

    len = LHStrLen(src);

    s = (char *) malloc(len + 1);
    if (s == NULL)
        return NULL;

	memcpy (s, LHStrBuf(src), len);
    s[len] = '\0';

    return s;
}

MgErr ftw_support_buffer_to_LStrHandle(LStrHandle *dest, const void *src, size_t length)
{
    MgErr lv_err;

    if (src == NULL)
        return mgArgErr;

    lv_err = NumericArrayResize(uB, 1, (UHandle *)dest, length);
    if (lv_err == mgNoErr) {
        MoveBlock(src, LHStrBuf(*dest), length);
        (**dest)->cnt = (int32)length;
    }
    return lv_err;
}

MgErr ftw_support_CStr_to_LStrHandle(LStrHandle *dest, const char *src, size_t max_length)
{
    MgErr lv_err;
    size_t len;

    if (src == NULL)
        return mgArgErr;

    len = strnlen(src, max_length);
    lv_err = ftw_support_buffer_to_LStrHandle(dest, src, len);

    return lv_err;
}

MgErr ftw_support_expand_LStrHandleArray(LStrHandleArray ***arr, size_t elements)
{
    MgErr lv_err;

    if (arr == NULL || *arr == NULL || **arr == NULL)
        return mgArgErr;

    lv_err = NumericArrayResize(uL, 1, (UHandle *)arr, elements);

    if (lv_err == mgNoErr)
        (**arr)->dimsize = (int32)elements;

    return lv_err;
}

MgErr ftw_support_expand_PointerArray(PointerArray ***arr, size_t elements)
{
    MgErr lv_err;
    int32 sz;

    if (arr == NULL || *arr == NULL || **arr == NULL)
        return mgArgErr;

    FTW_COMPILER_ASSERT(sizeof(void*) == 8 || sizeof(void*) == 4);
    
    if (sizeof(void*) == 8)
        sz = uQ;
    else if (sizeof(void*) == 4)
        sz = uL;
    else
        ftw_assert_unreachable("Compiler assertion failed.");

    lv_err = NumericArrayResize(sz, 1, (UHandle *)arr, elements);
    if (lv_err == mgNoErr)
        (**arr)->dimsize = (int32)elements;

    return lv_err;
}

MgErr ftw_support_expand_int32Array(int32Array ***arr, size_t elements)
{
    MgErr lv_err;

    if (arr == NULL || *arr == NULL || **arr == NULL)
        return mgArgErr;

    lv_err = NumericArrayResize(uL, 1, (UHandle *)arr, elements);

    if (lv_err == mgNoErr)
        (**arr)->dimsize = (int32)elements;

    return lv_err;
}

