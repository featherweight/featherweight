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

#ifndef FTW_SQLITE_H_INCLUDED
#define FTW_SQLITE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define SQLITE_HAVE_ISNAN 1

#include "../ftw.h"
#include "upstream/sqlite3.c"

    /*  Thin wrappers for SQLite functions to export. */
    FTW_EXPORT const char *ftw_sqlite_errstr(ftwrc code, LStrHandle lib_version);

    FTW_EXPORT ftwrc ftw_sqlite_open(const char *path, sqlite3 **connection, int flags, LStrHandle lib_version);
    FTW_EXPORT ftwrc ftw_sqlite_close(sqlite3 *connection);

    FTW_EXPORT ftwrc ftw_sqlite_transaction_begin(sqlite3 *connection);
    FTW_EXPORT ftwrc ftw_sqlite_transaction_end(sqlite3 *connection);

    FTW_EXPORT ftwrc ftw_sqlite_prepare(sqlite3 *connection, ConstLStrH sql, PointerArray **statements);
    FTW_EXPORT ftwrc ftw_sqlite_step(sqlite3_stmt *statement);
    FTW_EXPORT ftwrc ftw_sqlite_reset(sqlite3_stmt *statement);
    FTW_EXPORT ftwrc ftw_sqlite_parameters(sqlite3_stmt *statement, LStrHandleArray **parameters);
    FTW_EXPORT ftwrc ftw_sqlite_finalize(sqlite3_stmt *pStmt);

    FTW_EXPORT int64 ftw_column_int64(sqlite3_stmt *statement, int32 col);
    FTW_EXPORT float64 ftw_column_float64(sqlite3_stmt *statement, int32 col);
    FTW_EXPORT ftwrc ftw_column_string(sqlite3_stmt *statement, int32 col, LStrHandle value);
    FTW_EXPORT ftwrc ftw_column_blob(sqlite3_stmt *statement, int32 col, LStrHandle value);

    FTW_EXPORT ftwrc ftw_sqlite_bind_int64(sqlite3_stmt *statement, int32 index, int64 value);
    FTW_EXPORT ftwrc ftw_sqlite_bind_float64(sqlite3_stmt *statement, int32 index, float64 value);
    FTW_EXPORT ftwrc ftw_sqlite_bind_string(sqlite3_stmt *statement, int32 index, ConstLStrH value);
    FTW_EXPORT ftwrc ftw_sqlite_bind_blob(sqlite3_stmt *statement, int32 index, ConstLStrH value);

    FTW_EXPORT ftwrc ftw_sqlite_finalize(sqlite3_stmt *statement);

    FTW_EXPORT sqlite3_backup *ftw_sqlite_backup_init(sqlite3* pDestDb, const char *zDestDb, sqlite3* pSrcDb, const char *zSrcDb);
    FTW_EXPORT ftwrc ftw_sqlite_backup_step(sqlite3_backup *p, int nPage);
    FTW_EXPORT ftwrc ftw_sqlite_backup_finish(sqlite3_backup *p);

    FTW_EXPORT ftwrc ftw_sqlite_randomness(LStrHandle buf);

#ifdef __cplusplus
}
#endif

#endif
