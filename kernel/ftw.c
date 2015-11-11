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

MgErr ftw_support_buffer_to_LStrHandle(LStrHandle *dest, const void *src, size_t length)
{
    MgErr lv_err;

    if (src == NULL)
        return mgArgErr;

    lv_err = NumericArrayResize(uB, 1, (UHandle *)dest, length);
    if (lv_err == mgNoErr) {
        MoveBlock(src, LHStrBuf(*dest), length);
        LStrLen(**dest) = length;
    }
    return lv_err;
}

MgErr ftw_support_CStr_to_LStrHandle(LStrHandle *dest, const char *src)
{
    MgErr lv_err;
    size_t len;

    if (src == NULL)
        return mgArgErr;

    len = StrLen(src);
    lv_err = ftw_support_buffer_to_LStrHandle(dest, src, len);

    return lv_err;
}

MgErr ftw_support_resize_PointerArray(PointerArray **arr, size_t elements)
{
    MgErr rc;
    size_t bytes;

    if (arr == NULL || *arr == NULL)
        return mgArgErr;

    bytes = ftw_support_sizeof_array(PointerArray, elements);

    rc = NumericArrayResize(uB, 1, (UHandle *)&arr, bytes);

    if (rc == mgNoErr)
        (*arr)->dimsize = (int32_t)elements;

    return rc;
}

MgErr ftw_support_resize_LStrHandleArray(LStrHandleArray **arr, size_t elements)
{
    MgErr rc;

    if (arr == NULL || *arr == NULL)
        return mgArgErr;

    rc = NumericArrayResize(uL, 1, (UHandle *)&arr, elements);

    if (rc == mgNoErr)
        (*arr)->dimsize = (int32_t)elements;

    return rc;
}
