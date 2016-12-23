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

#include "ftw_json.h"

json_t *ftw_json_new_from_string(const LStrHandle string, size_t flags, int64 *err_line,
    int64 *err_column, int64 *err_position, LStrHandle err_source, LStrHandle err_hint)
{
    json_error_t err;
    json_t *parsed;
    size_t len;
    const char *buf;

    buf = LHStrBuf(string);
    len = LHStrLen(string);

    parsed = json_loadb(buf, len, flags, &err);

    /*  Invalid JSON in the buffer is an error condition indicated by NULL. */
    if (parsed == NULL) {
        *err_line = err.line;
        *err_column = err.column;
        *err_position = err.position;
        ftw_support_CStr_to_LStrHandle(&err_source, err.source, sizeof(err.source));
        ftw_support_CStr_to_LStrHandle(&err_hint, err.text, sizeof(err.text));
    }

    return parsed;
}


void ftw_json_get_integer(json_t *obj, uint8_t *type, const char *key, LVBoolean *remove, int64_t *value)
{
    json_t *element;

    element = json_object_get(obj, key);

    if (element == NULL) {
        *remove = LVBooleanFalse;
        return;
    }

    *type = json_typeof(element);
    *value = json_integer_value(element);

    if (*remove == LVBooleanTrue) {
        json_object_del(obj, key);
    }

    return;
}

void ftw_json_get_boolean(json_t *obj, uint8_t *type, const char *key, LVBoolean *remove, LVBoolean *value)
{
    json_t *element;

    element = json_object_get(obj, key);

    if (element == NULL) {
        *remove = LVBooleanFalse;
        return;
    }

    *type = json_typeof(element);
    *value = json_boolean_value(element);

    if (*remove == LVBooleanTrue) {
        json_object_del(obj, key);
    }

    return;
}

void ftw_json_get_float64(json_t *obj, uint8_t *type, const char *key, LVBoolean *remove, float64 *value)
{
    json_t *element;

    element = json_object_get(obj, key);

    if (element == NULL) {
        *remove = LVBooleanFalse;
        return;
    }

    switch (*type = json_typeof(element)) {
    case JSON_REAL:
        *value = json_real_value(element);
        break;
    case JSON_INTEGER:
        *value = (float64)json_integer_value(element);
        break;
    default:
        break;
    }

    if (*remove == LVBooleanTrue) {
        json_object_del(obj, key);
    }

    return;
}

void ftw_json_get_string(json_t *obj, uint8_t *type, const char *key, LVBoolean *remove, LStrHandle value)
{
    ftwrc rc;
    json_t *element;

    element = json_object_get(obj, key);

    if (element == NULL) {
        *remove = LVBooleanFalse;
        return;
    }

    *type = json_typeof(element);

    rc = ftw_support_buffer_to_LStrHandle(&value, json_string_value(element), json_string_length(element));

    if (rc != EFTWOK)
        return;

    if (*remove == LVBooleanTrue) {
        json_object_del(obj, key);
    }

    return;
}

ftwrc ftw_json_set_integer(json_t *obj, const char *key, int64_t *value)
{
    if (value == NULL)
        return -1;

    return json_object_set_new(obj, key, json_integer(*value));
}

ftwrc ftw_json_set_boolean(json_t *obj, const char *key, LVBoolean *value)
{
    if (value == NULL)
        return -1;

    return json_object_set_new(obj, key, json_boolean(*value == LVBooleanTrue));
}

ftwrc ftw_json_set_float64(json_t *obj, const char *key, float64 *value)
{
    json_t *newval;

    if (value == NULL)
        return -1;

    if (isinf(*value))
        return -1;

    newval = (isnan(*value) ? json_null() : json_real(*value));

    return json_object_set_new(obj, key, newval);
}

ftwrc ftw_json_set_string(json_t *obj, const char *key, LStrHandle value)
{
    if (value == NULL)
        return -1;

    return json_object_set_new(obj, key, json_stringn(LHStrBuf(value), LHStrLen(value)));
}

ftwrc ftw_json_set_null(json_t *obj, const char *key)
{
    return json_object_set(obj, key, json_null());
}

ftwrc ftw_json_object_keys(json_t *object, LStrHandleArray **keys)
{
    const char *key;
    void *iterator;
    int count;
    int i;
    ftwrc rc;

    if (object == NULL) {
        return EFTWARG;
    }

    iterator = json_object_iter(object);

    count = 0;

    while (iterator) {
        count++;
        iterator = json_object_iter_next(object, iterator);
    }

    if (count == 0) {
        return EFTWOK;
    }

    rc = ftw_support_expand_LStrHandleArray(&keys, count);
    if (rc) {
        return rc;
    }

    i = 0;
    iterator = json_object_iter(object);

    while (iterator)
    {
        key = json_object_iter_key(iterator);
        ftw_assert(key != NULL);

        rc = ftw_support_CStr_to_LStrHandle(&(*keys)->element[i], key, StrLen(key));
        if (rc) {
            break;
        }

        i++;
        (*keys)->dimsize = i;

        iterator = json_object_iter_next(object, iterator);
    }

    return rc;
}

void ftw_json_element_type(json_t *element, uint8_t *type)
{
    if (element == NULL)
        return;

    *type = json_typeof(element);

    return;
}


ftwrc ftw_json_serialize_element(const json_t *json, size_t flags, LStrHandle serialized)
{
    char *buffer;
    int32 length;
    ftwrc rc;

    buffer = json_dumps(json, flags);

    if (buffer == NULL) {
        return EFTWNOMEM;
    }

    length = StrLen(buffer);

    rc = ftw_support_CStr_to_LStrHandle(&serialized, buffer, length);

    free(buffer);

    return rc;
}

ftwrc ftw_json_serialize_and_destroy(json_t *json, size_t flags, LStrHandle serialized)
{
    ftwrc rc;

    rc = ftw_json_serialize_element(json, flags, serialized);

    json_decref(json);

    return rc;
}

void ftw_json_destroy(json_t *value)
{
    json_decref (value);

    return;
}

json_t *ftw_json_deep_copy(const json_t *value)
{
    return json_deep_copy(value);
}

void ftw_json_object_equal(json_t *object, json_t *other, LVBoolean *equal)
{
    int rc;

    rc = json_equal(object, other);

    *equal = rc ? LVBooleanTrue : LVBooleanFalse;

    return;
}

json_t *ftw_json_object_get(const json_t *obj, const char *key)
{
    return json_object_get(obj, key);
}

ftwrc ftw_json_array_elements(const json_t *array, PointerArray **items)
{
    size_t num_items;
    size_t i;
    ftwrc rc;

    if (items == NULL) {
        return EFTWARG;
    }

    num_items = json_array_size(array);

    rc = ftw_support_expand_PointerArray(&items, num_items);
    if (rc)
        return rc;

    for (i=0; i<num_items; i++) {
        (*items)->element[i] = (intptr_t)json_array_get(array, i);
    }

    return EFTWOK;
}


int64_t ftw_json_val_integer (const json_t *val)
{
    return json_integer_value(val);
}

ftwrc ftw_json_val_string (const json_t *val, LStrHandle string)
{
    const char *buf;
    size_t len;
    ftwrc rc;

    buf = json_string_value(val);
    len = json_string_length(val);

    rc = ftw_support_buffer_to_LStrHandle(&string, buf, len);

    return rc;
}

double ftw_json_val_double (const json_t *val)
{
    return json_number_value(val);
}

ftwrc ftw_json_object_join(enum json_join_mode *mode, json_t *object, json_t *obj_to_join)
{
    int rc;

    if (mode == NULL)
        return -1;

    switch (*mode) {
    case UPSERT:
        rc = json_object_update (object, obj_to_join);
        break;
    case UPDATE:
        rc = json_object_update_existing (object, obj_to_join);
        break;
    case INSERT:
        rc = json_object_update_missing (object, obj_to_join);
        break;
    default:
        rc = -1;
        break;
    }

    return (rc == 0 ? EFTWOK : EFTWARG);
}

ftwrc ftw_json_object_clear(json_t *object)
{
    int rc;

    rc = json_object_clear(object);

    return (rc == 0 ? EFTWOK : EFTWARG);
}

ftwrc ftw_json_object_delete(json_t *object, const char *key)
{
    int rc;

    rc = json_object_del(object, key);

    return (rc == 0 ? EFTWOK : EFTWARG);
}
