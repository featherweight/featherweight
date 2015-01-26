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

#include "ftw_json.h"

void ftw_json_get_integer(const json_t *obj, const char *key, int64_t *value, LVBoolean *exists)
{
    json_t *element;

    element = json_object_get(obj, key);

    if (element == NULL) {
        *exists = LVBooleanTrue;
        return;
    }

    *value = json_integer_value(element);

    return;
}

void ftw_json_get_boolean(const json_t *obj, const char *key, LVBoolean *value, LVBoolean *exists)
{
    return;
}

void ftw_json_get_float64(const json_t *obj, const char *key, float64 *value, LVBoolean *exists)
{
    return;
}

void ftw_json_get_string(const json_t *obj, const char *key, LStrHandle value, LVBoolean *exists)
{
    return;
}

int ftw_json_object_join (json_t *object, json_t *obj_to_join, enum json_join_mode mode)
{
    return 0;
}

void ftw_json_object_equal (json_t *object, json_t *other, LVBoolean *equal)
{
    return;
}

int ftw_json_object_keys (json_t *object, LStrHandleArray **keys)
{
    return 0;
}
