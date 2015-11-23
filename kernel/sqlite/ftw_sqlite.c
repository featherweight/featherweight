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

#include "ftw_sqlite.h"

const char *ftw_sqlite_libversion(void)
{
    return sqlite3_libversion();
}

const char *ftw_sqlite_errstr(int rc)
{
    return sqlite3ErrStr(rc);
}

int ftw_sqlite_open(const char *path, sqlite3 **connection, int flags)
{
    return sqlite3_open_v2(path, connection, flags, NULL);
}

int ftw_sqlite_close(sqlite3 *connection)
{
    return sqlite3_close_v2(connection);
}

int ftw_sqlite_prepare(sqlite3 *connection, ConstLStrH sql, PointerArray **statements)
{
    sqlite3_stmt *prepared_statement;
    MgErr lv_err;
    int max_statements;
    const char *ptr;
    char *next_ptr;
    int len;
    int rc;
    int count;

    /*  The LabVIEW wrapper is expected to have preallocated this array with an
        arbitrarily-large enough buffer to accomodate all prepared statements. */
    if (statements == NULL || *statements == NULL)
        return SQLITE_MISUSE;

    max_statements = (*statements)->dimsize;
    ptr = LHStrBuf(sql);
    len = LHStrLen(sql);

    if (len == 0)
        return SQLITE_OK;

    for (count = 0; count < max_statements && len > 0; count++) {
        rc = sqlite3_prepare_v2(connection, ptr, len, &prepared_statement, &next_ptr);
        if (rc != SQLITE_OK || prepared_statement == NULL)
            break;
        (*statements)->element[count] = (intptr_t)prepared_statement;
        len -= next_ptr - ptr;
        ftw_assert(len >= 0);
        ptr = next_ptr;

    }

    lv_err = ftw_support_expand_PointerArray(&statements, count);
    if (lv_err != mgNoErr)
        return SQLITE_NOMEM;

    return rc;
}

int ftw_sqlite_step(sqlite3_stmt *statement)
{
    return sqlite3_step(statement);
}

int ftw_sqlite_reset(sqlite3_stmt *statement)
{
    return sqlite3_reset(statement);
}

MgErr ftw_sqlite_parameters(sqlite3_stmt *statement, LStrHandleArray **parameters)
{
    MgErr lv_err;
    const char *param_name;
    int count;

    count = sqlite3_bind_parameter_count(statement);
    lv_err = ftw_support_expand_LStrHandleArray(&parameters, count);
    if (lv_err)
        return lv_err;

    for (int i = 0; i < count; i++) {
        param_name = sqlite3_bind_parameter_name(statement, i + 1);
        lv_err = ftw_support_CStr_to_LStrHandle(&(*parameters)->element[i], param_name, strlen(param_name));
        if (lv_err)
            break;
    }

    return lv_err;
}

int ftw_sqlite_finalize(sqlite3_stmt *statement)
{
    return sqlite3_finalize(statement);
}

int64 ftw_column_int64(sqlite3_stmt *statement, int32 col)
{
    return sqlite3_column_int64(statement, col);
}

float64 ftw_column_float64(sqlite3_stmt *statement, int32 col)
{
    return sqlite3_column_double(statement, col);
}

MgErr ftw_column_string(sqlite3_stmt *statement, int32 col, LStrHandle value)
{
    MgErr lv_err;
    const char *col_value;

    col_value = sqlite3_column_text(statement, col);

    lv_err = ftw_support_CStr_to_LStrHandle(&value, col_value, strlen(col_value));

    return lv_err;
}

MgErr ftw_column_blob(sqlite3_stmt *statement, int32 col, LStrHandle value)
{
    MgErr lv_err;
    const void *col_value;
    int len;

    col_value = sqlite3_column_blob(statement, col);
    len = sqlite3_column_bytes(statement, col);

    lv_err = ftw_support_buffer_to_LStrHandle(&value, col_value, len);

    return lv_err;
}

int ftw_sqlite_bind_int64(sqlite3_stmt *statement, int32 index, int64 value)
{
    return sqlite3_bind_int64(statement, index, value);
}

int ftw_sqlite_bind_float64(sqlite3_stmt *statement, int32 index, float64 value)
{
    return sqlite3_bind_double(statement, index, value);
}

int ftw_sqlite_bind_string(sqlite3_stmt *statement, int32 index, ConstLStrH value)
{
    return sqlite3_bind_text64(statement, index, LHStrBuf(value), LHStrLen(value), SQLITE_TRANSIENT, SQLITE_UTF8);
}

int ftw_sqlite_bind_blob(sqlite3_stmt *statement, int32 index, ConstLStrH value)
{
    return sqlite3_bind_blob64(statement, index, LHStrBuf(value), LHStrLen(value), SQLITE_TRANSIENT);
}

sqlite3_backup *ftw_sqlite_backup_init(sqlite3* pDestDb, const char *zDestDb, sqlite3* pSrcDb, const char *zSrcDb)
{
    return sqlite3_backup_init(pDestDb, zDestDb, pSrcDb, zSrcDb);
}

int ftw_sqlite_backup_step(sqlite3_backup *p, int nPage)
{
    return sqlite3_backup_step(p, nPage);
}

int ftw_sqlite_backup_finish(sqlite3_backup *p)
{
    return sqlite3_backup_finish(p);
}

int ftw_sqlite_randomness(LStrHandle buf)
{
    int rc;

    if (buf == NULL || *buf == NULL)
        return -1;

    rc = sqlite3_initialize();
    sqlite3_randomness(LHStrLen(buf), LHStrBuf(buf));
    return rc;
}
