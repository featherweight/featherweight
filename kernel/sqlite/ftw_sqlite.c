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

#include "ftw_sqlite.h"

const char *ftw_sqlite_errstr(ftwrc code, LStrHandle lib_version)
{
    const char *version;
    const char *err;

    version = sqlite3_libversion();

    if (ftw_support_CStr_to_LStrHandle(&lib_version, version, 1024) != EFTWOK) {
        return "LabVIEW is out of memory!";
    }

    switch (code) {
    case SQLITE_MISUSE:
        err = "Featherweight library developer error; please report this issue.";
        break;
    default:
        err = sqlite3ErrStr(code);
        break;
    }

    return err;
}

ftwrc ftw_sqlite_open(const char *path, sqlite3 **connection, int flags, LStrHandle lib_version)
{
    ftw_support_CStr_to_LStrHandle(&lib_version, sqlite3_libversion(), 1024);

    return sqlite3_open_v2(path, connection, flags, NULL);
}

ftwrc ftw_sqlite_close(sqlite3 *connection)
{
    return sqlite3_close_v2(connection);
}

ftwrc ftw_sqlite_transaction_begin(sqlite3 *connection)
{
    return sqlite3_exec(connection, "BEGIN", NULL, NULL, NULL);
}

ftwrc ftw_sqlite_transaction_end(sqlite3 *connection)
{
    return sqlite3_exec(connection, "END", NULL, NULL, NULL);
}

ftwrc ftw_sqlite_prepare(sqlite3 *connection, ConstLStrH sql, PointerArray **statements)
{
    sqlite3_stmt *prepared_statement;
    size_t max_statements;
    const char *ptr;
    const char *next_ptr;
    size_t count;
    ftwrc lvrc;
    int len;
    ftwrc rc;

    /*  The LabVIEW wrapper is expected to have preallocated this array with an
        arbitrarily-large enough buffer to accomodate all prepared statements. */
    if (statements == NULL || *statements == NULL) {
        return SQLITE_MISUSE;
    }

    max_statements = (*statements)->dimsize;

    if (max_statements <= 0) {
        return SQLITE_MISUSE;
    }

    ptr = LHStrBuf(sql);
    len = LHStrLen(sql);

    rc = SQLITE_OK;

    for (count = 0; count < max_statements && len > 0; count++) {
        rc = sqlite3_prepare_v2(connection, ptr, len, &prepared_statement, &next_ptr);
        if (rc != SQLITE_OK || prepared_statement == NULL) {
            break;
        }
        (*statements)->element[count] = (intptr_t)prepared_statement;
        len -= next_ptr - ptr;
        ftw_assert(len >= 0);
        ptr = next_ptr;
    }

    lvrc = ftw_support_expand_PointerArray(&statements, count);
    if (lvrc != EFTWOK) {
        return SQLITE_NOMEM;
    }

    return rc;
}

ftwrc ftw_sqlite_step(sqlite3_stmt *statement)
{
    return sqlite3_step(statement);
}

ftwrc ftw_sqlite_reset(sqlite3_stmt *statement)
{
    return sqlite3_reset(statement);
}

ftwrc ftw_sqlite_parameters(sqlite3_stmt *statement, LStrHandleArray **parameters)
{
    const char *param_name;
    ftwrc rc;
    int count;
    int i;

    count = sqlite3_bind_parameter_count(statement);
    rc = ftw_support_expand_LStrHandleArray(&parameters, count);
    if (rc) {
        return rc;
    }

    for (i = 0; i < count; i++) {
        param_name = sqlite3_bind_parameter_name(statement, i + 1);
        rc = ftw_support_CStr_to_LStrHandle(&(*parameters)->element[i], param_name, strlen(param_name));
        if (rc)
            break;
    }

    return rc;
}

ftwrc ftw_sqlite_finalize(sqlite3_stmt *statement)
{
    ftwrc rc;

    rc = sqlite3_finalize(statement);

    /*  Filter away "obvious" return code. */
    return (rc == SQLITE_DONE ? SQLITE_OK : rc);
}

int64 ftw_column_int64(sqlite3_stmt *statement, int32 col)
{
    return sqlite3_column_int64(statement, col);
}

float64 ftw_column_float64(sqlite3_stmt *statement, int32 col)
{
    int rc;

    rc = sqlite3_column_type(statement, col);

    if (rc == SQLITE_NULL) {
        return FTW_NaN;
    }
    else {
        return sqlite3_column_double(statement, col);
    }
}

ftwrc ftw_column_string(sqlite3_stmt *statement, int32 col, LStrHandle value)
{
    const unsigned char *col_value;
    ftwrc rc;

    col_value = sqlite3_column_text(statement, col);

    rc = ftw_support_CStr_to_LStrHandle(&value, col_value, strlen(col_value));

    return rc;
}

ftwrc ftw_column_blob(sqlite3_stmt *statement, int32 col, LStrHandle value)
{
    const void *col_value;
    ftwrc rc;
    int len;

    col_value = sqlite3_column_blob(statement, col);
    len = sqlite3_column_bytes(statement, col);

    rc = ftw_support_buffer_to_LStrHandle(&value, col_value, len, 0);

    return rc;
}

ftwrc ftw_sqlite_bind_int64(sqlite3_stmt *statement, int32 index, int64 value)
{
    return sqlite3_bind_int64(statement, index, value);
}

ftwrc ftw_sqlite_bind_float64(sqlite3_stmt *statement, int32 index, float64 value)
{
    return sqlite3_bind_double(statement, index, value);
}

ftwrc ftw_sqlite_bind_string(sqlite3_stmt *statement, int32 index, ConstLStrH value)
{
    return sqlite3_bind_text64(statement, index, LHStrBuf(value), LHStrLen(value), SQLITE_TRANSIENT, SQLITE_UTF8);
}

ftwrc ftw_sqlite_bind_blob(sqlite3_stmt *statement, int32 index, ConstLStrH value)
{
    return sqlite3_bind_blob64(statement, index, LHStrBuf(value), LHStrLen(value), SQLITE_TRANSIENT);
}

sqlite3_backup *ftw_sqlite_backup_init(sqlite3* pDestDb, const char *zDestDb, sqlite3* pSrcDb, const char *zSrcDb)
{
    return sqlite3_backup_init(pDestDb, zDestDb, pSrcDb, zSrcDb);
}

ftwrc ftw_sqlite_backup_step(sqlite3_backup *p, int nPage)
{
    return sqlite3_backup_step(p, nPage);
}

ftwrc ftw_sqlite_backup_finish(sqlite3_backup *p)
{
    return sqlite3_backup_finish(p);
}

ftwrc ftw_sqlite_randomness(LStrHandle buf)
{
    ftwrc rc;

    if (buf == NULL || *buf == NULL) {
        return EFTWARG;
    }

    rc = sqlite3_initialize();
    sqlite3_randomness(LHStrLen(buf), LHStrBuf(buf));
    return rc;
}
