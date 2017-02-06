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

FTW_PRIVATE_SUPPORT ftwrc ftw_json_traverse_path(json_t **node, const char *path, LVBoolean *remove)
{
    const char *start;
    const char *pos;
    size_t index, len;
    json_type t;
    void *iter;

    if (path == NULL) {
        return EFTWARG;
    }

    /*  Return early as a silent no-op if the node doesn't exist. */
    if (*node == NULL) {
        return EFTWOK;
    }

    /*  Return early as a "select self" when path is empty. */
    if (path[0] == '\0') {
        if (remove) {
            *remove = LVBooleanFalse;
        }
        return EFTWOK;
    }

    pos = path;
    while (*node && pos[0] != '\0') {

        t = json_typeof(*node);

        switch (pos[0]) {
        case '.':
            /*  Dot-notation only works for objects. */
            if (t != JSON_OBJECT) {
                *node = NULL;
                return EFTWARG;
            }
            pos++;
            /*  Dot-notation requires a node name to come after the dot. */
            if (pos[0] == '\0' || pos[0] == '[') {
                *node = NULL;
                return EFTWARG;
            }

            break;

        case '[':
            /*  Bracket-index notation is enabled for both arrays and objects. */
            if (t != JSON_ARRAY && t != JSON_OBJECT) {
                *node = NULL;
                return EFTWARG;
            }
            pos++;
            /*  Bracket-index notation requires an unsigned integer between brackets. */
            if (pos[0] < '0' || pos[0] > '9') {
                *node = NULL;
                return EFTWARG;
            }

            index = 0;
            len = 0;
            while ('0' <= pos[0] && pos[0] <= '9') {
                index = index * 10 + pos[0] - '0';
                pos++;
            }

            /*  Bracket-notation requires closing bracket. */
            if (pos[0] != ']') {
                *node = NULL;
                return EFTWARG;
            }

            pos++;

            /* Continue parsing if more string remains -OR- finished parsing and ready to return borrowed reference. */
            if ((pos[0] != '\0') || (remove == NULL || *remove == LVBooleanFalse)) {
                switch (t) {
                case JSON_ARRAY:
                    *node = json_array_get(*node, index);
                    break;
                case JSON_OBJECT:
                    for(iter = json_object_iter(*node); iter && index > 0; iter = json_object_iter_next(*node, iter)) {
                        index --;
                    }
                    *node = json_object_iter_value (iter);
                    break;
                default:
                    ftw_assert_unreachable("Function should have already returned with error code.");
                    break;
                }
            }
            else {
                /*  Finished parsing; prepare to return stolen reference. */
                switch (t) {
                case JSON_ARRAY:
                    *node = json_array_steal(*node, index);
                    break;
                case JSON_OBJECT:
                    for(iter = json_object_iter(*node); iter && index > 0; iter = json_object_iter_next(*node, iter)) {
                        index --;
                    }
                    *node = json_object_steal(*node, json_object_iter_key(iter));
                    break;
                default:
                    ftw_assert_unreachable("Function should have already returned with error code.");
                    break;
                }
                *remove = (*node ? LVBooleanTrue : LVBooleanFalse);

            }

            break;

        case '"':
            /*  Addressing by key only works for objects. */
            if (t != JSON_OBJECT) {
                *node = NULL;
                return EFTWARG;
            }

            pos++;
            len = 0;
            start = pos;
            while (pos[0] != '\0' && pos[0] != '"') {
                pos++;
                len++;
            }

            /*  Quoting a key name requires an end quote. */
            if (pos[0] == '\0') {
                *node = NULL;
                return EFTWARG;
            }

            ftw_assert(pos[0] == '"');
            pos++;

            if (pos[0] != '\0') {
                /* Continue parsing. */
                *node = json_object_getn(*node, start, len);
            }
            else if (remove == NULL || *remove == LVBooleanFalse) {
                /*  Finished parsing; prepare to return borrowed reference. */
                *node = json_object_getn(*node, start, len);
            }
            else {
                /*  Finished parsing; prepare to return stolen reference. */
                *node = json_object_stealn(*node, start, len);
                *remove = (*node ? LVBooleanTrue : LVBooleanFalse);
            }

            break;

        default:
            /*  This starting character must be a key to an object. */
            if (t != JSON_OBJECT) {
                *node = NULL;
                return EFTWARG;
            }
            len = 0;
            start = pos;
            while (pos[0] != '\0' && pos[0] != '.' && pos[0] != '[') {
                pos++;
                len++;
            }

            if (pos[0] != '\0') {
                /* Continue parsing. */
                *node = json_object_getn(*node, start, len);
            }
            else if (remove == NULL || *remove == LVBooleanFalse) {
                /*  Finished parsing; prepare to return borrowed reference. */
                *node = json_object_getn(*node, start, len);
            }
            else {
                /*  Finished parsing; prepare to return stolen reference. */
                *node = json_object_stealn(*node, start, len);
                *remove = (*node ? LVBooleanTrue : LVBooleanFalse);
            }

            break;
        }
    }

    return EFTWOK;
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

    rc = ftw_support_buffer_to_LStrHandle(&value, json_string_value(element), json_string_length(element), 0);

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
        return EFTWARG;

    return json_object_set_new(obj, key, json_integer(*value));
}

ftwrc ftw_json_set_boolean(json_t *obj, const char *key, LVBoolean *value)
{
    if (value == NULL)
        return EFTWARG;

    return json_object_set_new(obj, key, json_boolean(*value == LVBooleanTrue));
}

ftwrc ftw_json_set_float64(json_t *obj, const char *key, float64 *value)
{
    json_t *newval;

    if (value == NULL)
        return EFTWARG;

    if (isinf(*value))
        return EFTWARG;

    newval = (isnan(*value) ? json_null() : json_real(*value));

    return json_object_set_new(obj, key, newval);
}

ftwrc ftw_json_set_string(json_t *obj, const char *key, LStrHandle value)
{
    if (value == NULL)
        return EFTWARG;

    return json_object_set_new(obj, key, json_stringn(LHStrBuf(value), LHStrLen(value)));
}

ftwrc ftw_json_set_null(json_t *obj, const char *key)
{
    return json_object_set(obj, key, json_null());
}

ftwrc ftw_json_object_keys(json_t *element, const char *path, LStrHandleArray **keys)
{
    const char *key;
    void *iterator;
    size_t count;
    int i;
    ftwrc rc;

    rc = ftw_json_traverse_path(&element, path, NULL);
    if (rc != EFTWOK) {
        ftw_assert(element == NULL);
        return rc;
    }

    /*  Path is valid, but there was no element there. */
    if (element == NULL) {
        return EFTWOK;
    }

    count = json_object_size(element);
    if (count == 0) {
        return EFTWOK;
    }

    rc = ftw_support_expand_LStrHandleArray(&keys, count);
    if (rc) {
        return rc;
    }

    i = 0;
    iterator = json_object_iter(element);

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

        iterator = json_object_iter_next(element, iterator);
    }

    return rc;
}

void ftw_json_element_type(json_t *element, uint8_t *type)
{
    if (element == NULL) {
        return;
    }

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
    json_decref(value);

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

json_t *ftw_json_array_element(const json_t *array, size_t index)
{
    return json_array_get(array, index);
}

ftwrc ftw_json_traverse(json_t **element, const char *path, uint8_t *actual_type, LVBoolean *remove, uint32_t *size)
{
    ftwrc rc;

    rc = ftw_json_traverse_path(element, path, remove);
    if (rc != EFTWOK) {
        ftw_assert(*element == NULL);
        *remove = LVBooleanFalse;
        return rc;
    }

    /*  Path is valid, but there was no element there. */
    if (*element == NULL) {
        *remove = LVBooleanFalse;
        return EFTWOK;
    }

    switch (*actual_type = json_typeof(*element)) {

    case JSON_ARRAY:
        *size = (uint32_t)json_array_size(*element);
        break;

    case JSON_OBJECT:
        *size = (uint32_t)json_object_size(*element);
        break;

    default:
        *size = 0;
        break;
    }

    return EFTWOK;
}

ftwrc ftw_json_get_flat_boolean(json_t *element, const char *path, uint8_t *actual_type, LVBoolean *remove, LStrHandle flatval)
{
    ftwrc rc;

    rc = ftw_json_traverse_path(&element, path, remove);
    if (rc != EFTWOK) {
        ftw_assert(element == NULL);
        *remove = LVBooleanFalse;
        return rc;
    }

    /*  Path is valid, but there was no element there. */
    if (element == NULL) {
        *remove = LVBooleanFalse;
        return EFTWOK;
    }

    switch (*actual_type = json_typeof(element)) {
    case JSON_TRUE:
        (*flatval)->str[0] = LVBooleanTrue;
        break;
    case JSON_FALSE:
        (*flatval)->str[0] = LVBooleanFalse;
        break;
    default:
        /*  Element exists but is not of expected type. */
        break;
    }

    if (*remove) {
        json_decref(element);
    }

    return EFTWOK;
}

ftwrc ftw_json_get_flat_string(json_t *element, const char *path, uint8_t *actual_type, LVBoolean *remove, LStrHandle flatval, LVBoolean *prepend_len, size_t flags)
{
    size_t len, offset;
    ftwrc rc;

    rc = ftw_json_traverse_path(&element, path, remove);
    if (rc != EFTWOK) {
        ftw_assert(element == NULL);
        *remove = LVBooleanFalse;
        return rc;
    }

    /*  Path is valid, but there was no element there. */
    if (element == NULL) {
        *remove = LVBooleanFalse;
        return EFTWOK;
    }

    offset = *prepend_len ? sizeof (int32) : 0;

    switch (*actual_type = json_typeof(element)) {

    case JSON_STRING:
        {
            const char *buf = json_string_value(element);
            len = json_string_length(element);
            rc = ftw_support_buffer_to_LStrHandle(&flatval, buf, len, offset);
        }
        break;

    default:
        {
            char *buf = json_dumps(element, flags | JSON_ENCODE_ANY);
            if (buf == NULL) {
                rc = EFTWNOMEM;
            }
            else {
                len = StrLen(buf);
                rc = ftw_support_buffer_to_LStrHandle(&flatval, buf, len, offset);
                free(buf);
            }
        }
        break;
    }

    if (rc == EFTWOK && *prepend_len) {
        (*flatval)->str[0] = (uChar) ((len >> 0x18) & 0xFF);
        (*flatval)->str[1] = (uChar) ((len >> 0x10) & 0xFF);
        (*flatval)->str[2] = (uChar) ((len >> 0x08) & 0xFF);
        (*flatval)->str[3] = (uChar) ((len >> 0x00) & 0xFF);
    }

    if (*remove) {
        json_decref(element);
    }

    return rc;
}

ftwrc ftw_json_get_int(json_t *element, const char *path, uint8_t *actual_type, LVBoolean *remove, void *val, uint8_t *type_code, LVBoolean *flat)
{
    json_int_t value;
    json_int_t max, min;
    NumType t;
    ftwrc rc;

    t = (NumType) *type_code;

    switch (t) {
    case iQ:
        min = INT64_MIN;
        max = INT64_MAX;
        break;
    case iL:
        min = INT32_MIN;
        max = INT32_MAX;
        break;
    case iW:
        min = INT16_MIN;
        max = INT16_MAX;
        break;
    case iB:
        min = INT8_MIN;
        max = INT8_MAX;
        break;
    case uQ:
        /*  Not a typo; this max limitation is due to underlying signed representation. */
        min = 0;
        max = INT64_MAX;
        break;
    case uL:
        min = 0;
        max = UINT32_MAX;
        break;
    case uW:
        min = 0;
        max = UINT16_MAX;
        break;
    case uB:
        min = 0;
        max = UINT8_MAX;
        break;
    default:
        return EFTWARG;
    }

    rc = ftw_json_traverse_path(&element, path, remove);
    if (rc != EFTWOK) {
        ftw_assert(element == NULL);
        *remove = LVBooleanFalse;
        return rc;
    }

    /*  Path is valid, but there was no element there. */
    if (element == NULL) {
        *remove = LVBooleanFalse;
        return EFTWOK;
    }

    switch (*actual_type = json_typeof(element)) {

    case JSON_INTEGER:
        value = json_integer_value(element);
        break;

    case JSON_REAL:
        value = (json_int_t)json_real_value(element);
        break;

    case JSON_TRUE:
        value = 1;
        break;

    case JSON_FALSE:
        value = 0;
        break;

    default:
        /*  Element exists but is not of expected type. */
        goto VALUE_NOT_SET_RETURN_EARLY;
        break;
    }

    /*  Value would overflow the requested type. */
    if (value < min || value > max) {
        goto VALUE_NOT_SET_RETURN_EARLY;
    }

    if (*flat) {
        /*  Platform-independent big-endian byte order used for flattened data. */
        switch (t) {

        case iB:
        case uB:
            (*(LStrHandle)val)->str[0] = (uChar) ((value >> 0x00) & 0xFF);
            break;

        case iW:
        case uW:
            (*(LStrHandle)val)->str[0] = (uChar) ((value >> 0x08) & 0xFF);
            (*(LStrHandle)val)->str[1] = (uChar) ((value >> 0x00) & 0xFF);
            break;

        case iL:
        case uL:
            (*(LStrHandle)val)->str[0] = (uChar) ((value >> 0x18) & 0xFF);
            (*(LStrHandle)val)->str[1] = (uChar) ((value >> 0x10) & 0xFF);
            (*(LStrHandle)val)->str[2] = (uChar) ((value >> 0x08) & 0xFF);
            (*(LStrHandle)val)->str[3] = (uChar) ((value >> 0x00) & 0xFF);
            break;

        case iQ:
        case uQ:
            (*(LStrHandle)val)->str[0] = (uChar) ((value >> 0x38) & 0xFF);
            (*(LStrHandle)val)->str[1] = (uChar) ((value >> 0x30) & 0xFF);
            (*(LStrHandle)val)->str[2] = (uChar) ((value >> 0x28) & 0xFF);
            (*(LStrHandle)val)->str[3] = (uChar) ((value >> 0x20) & 0xFF);
            (*(LStrHandle)val)->str[4] = (uChar) ((value >> 0x18) & 0xFF);
            (*(LStrHandle)val)->str[5] = (uChar) ((value >> 0x10) & 0xFF);
            (*(LStrHandle)val)->str[6] = (uChar) ((value >> 0x08) & 0xFF);
            (*(LStrHandle)val)->str[7] = (uChar) ((value >> 0x00) & 0xFF);
            break;

        default:
            ftw_assert_unreachable("Function should have already returned with error code.");
            break;
        }
    }
    else {
        switch (t) {

        case iB:
            *(int8*)val = (int8)value;
            break;

        case iW:
            *(int16*)val = (int16)value;
            break;

        case iL:
            *(int32*)val = (int32)value;
            break;

        case iQ:
            *(int64*)val = (int64)value;
            break;

        case uB:
            *(uInt8*)val = (uInt8)value;
            break;

        case uW:
            *(uInt16*)val = (uInt16)value;
            break;

        case uL:
            *(uInt32*)val = (uInt32)value;
            break;

        case uQ:
            *(uInt64*)val = (uInt64)value;
            break;

        default:
            ftw_assert_unreachable("Function should have already returned with error code.");
            break;
        }
    }

    VALUE_NOT_SET_RETURN_EARLY:

    if (*remove) {
        json_decref(element);
    }

    return EFTWOK;
}

ftwrc ftw_json_get_scalar_double(json_t *element, const char *path, double *val, uint8_t *type, LVBoolean *remove)
{
    if (element == NULL)
        return EFTWARG;

    switch (*type = json_typeof(element)) {
    case JSON_INTEGER:
        *val = (double)json_integer_value(element);
        break;
    case JSON_REAL:
        *val = json_real_value(element);
        break;
    case JSON_NULL:
        *val = FTW_NaN;
        break;
    default:
        return EFTWARG;
    }

    if (*remove != LVBooleanFalse) {
        json_decref(element);
    }

    return EFTWOK;
}

ftwrc ftw_json_get_scalar_string(json_t *element, const char *path, LStrHandle val, uint8_t *type, LVBoolean *remove)
{
    const char *buf;
    size_t len;
    ftwrc rc;

    if (element == NULL)
        return EFTWARG;

    switch (*type = json_typeof(element)) {
    case JSON_STRING:
        buf = json_string_value(element);
        len = json_string_length(element);
        rc = ftw_support_buffer_to_LStrHandle(&val, buf, len, 0);
        break;
    default:
        buf = json_dumps(element, JSON_ENCODE_ANY);
        len = StrLen(buf);
        rc = ftw_support_buffer_to_LStrHandle(&val, buf, len, 0);
        break;
    }

    if (rc != EFTWOK) {
        return rc;
    }

    if (*remove != LVBooleanFalse) {
        json_decref(element);
    }

    return EFTWOK;
}

ftwrc ftw_json_object_join(enum json_join_mode *mode, json_t *object, json_t *obj_to_join)
{
    int rc;

    if (mode == NULL)
        return EFTWARG;

    switch (*mode) {
    case UPSERT:
        rc = json_object_update(object, obj_to_join);
        break;
    case UPDATE:
        rc = json_object_update_existing(object, obj_to_join);
        break;
    case INSERT:
        rc = json_object_update_missing(object, obj_to_join);
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
