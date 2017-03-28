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

#ifndef FTW_JSON_H_INCLUDED
#define FTW_JSON_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "../ftw.h"
#include "upstream/src/jansson.h"

    /*  Object join modes. */
    enum json_join_mode {
        UPSERT, /*  Update or insert. */
        UPDATE, /*  Update existing keys, and silently skip creating new keys. */
        INSERT  /*  Insert new keys, and silently skip updating existing keys. */
    };

    FTW_EXPORT json_t *ftw_json_new_from_string(const LStrHandle string, size_t flags, int64 *err_line,
        int64 *err_column, int64 *err_position, LStrHandle err_source, LStrHandle err_hint);
    FTW_EXPORT json_t *ftw_json_deep_copy(const json_t *value);

    FTW_EXPORT ftwrc ftw_json_set_integer(json_t *obj, const char *key, int64_t *value);
    FTW_EXPORT ftwrc ftw_json_set_boolean(json_t *obj, const char *key, LVBoolean *value);
    FTW_EXPORT ftwrc ftw_json_set_float64(json_t *obj, const char *key, float64 *value);
    FTW_EXPORT ftwrc ftw_json_set_string(json_t *obj, const char *key, LStrHandle value);
    FTW_EXPORT ftwrc ftw_json_set_null(json_t *obj, const char *key);

    FTW_EXPORT json_t *ftw_json_array_element(const json_t *array, size_t index);

    FTW_EXPORT ftwrc ftw_json_fetch_boolean(json_t *element, const char *path, uint8_t *actual_type, LVBoolean *remove, const LVBoolean *flat, void *val);
    FTW_EXPORT ftwrc ftw_json_fetch_integer(json_t *element, const char *path, uint8_t *actual_type, LVBoolean *remove, const LVBoolean *flat, void *val, uint8_t *type_code);
    FTW_EXPORT ftwrc ftw_json_fetch_float(json_t *element, const char *path, uint8_t *actual_type, LVBoolean *remove, const LVBoolean *flat, void *val, uint8_t *type_code);
    FTW_EXPORT ftwrc ftw_json_fetch_string(json_t *element, const char *path, uint8_t *actual_type, LVBoolean *remove, const LVBoolean *flat, LStrHandle flatval, size_t flags);
    FTW_EXPORT ftwrc ftw_json_traverse(json_t **element, const char *path, uint8_t *actual_type, LVBoolean *remove, uint32_t *size);

    FTW_EXPORT ftwrc ftw_json_object_join(enum json_join_mode *mode, json_t *object, json_t *obj_to_join);
    FTW_EXPORT void ftw_json_object_equal(json_t *object, json_t *other, LVBoolean *equal);
    FTW_EXPORT ftwrc ftw_json_object_keys(json_t *object, const char *path, LStrHandleArray **keys);
    FTW_EXPORT ftwrc ftw_json_object_clear(json_t *object);
    FTW_EXPORT ftwrc ftw_json_object_delete(json_t *object, const char *key);

    FTW_EXPORT void ftw_json_element_type(json_t *element, uint8_t *type);
    FTW_EXPORT ftwrc ftw_json_serialize_element(const json_t *json, size_t flags, LStrHandle serialized);
    FTW_EXPORT ftwrc ftw_json_serialize_and_destroy(json_t *json, size_t flags, LStrHandle serialized);
    FTW_EXPORT void ftw_json_destroy(json_t *value);

#ifdef __cplusplus
}
#endif

#endif