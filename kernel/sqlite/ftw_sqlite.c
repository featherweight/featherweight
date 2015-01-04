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

FTW_EXPORT int ftw_sqlite_initialize(void)
{
    return sqlite3_initialize();
}

FTW_EXPORT const char *ftw_sqlite_libversion(void)
{
    return sqlite3_libversion();
}

FTW_EXPORT const char *ftw_sqlite_errstr(int rc)
{
    return sqlite3ErrStr(rc);
}

FTW_EXPORT int ftw_sqlite_open(const char *filename, sqlite3 **ppDb, int flags, const char *zVfs)
{
    return sqlite3_open_v2(filename, ppDb, flags, zVfs);
}

FTW_EXPORT int ftw_sqlite_close(sqlite3 *db)
{
    return sqlite3_close_v2(db);
}

FTW_EXPORT int ftw_sqlite_prepare(sqlite3 *db, const char *zSql, int nBytes, sqlite3_stmt **ppStmt, const char **pzTail)
{
    return sqlite3_prepare_v2(db, zSql, nBytes, ppStmt, pzTail);
}

FTW_EXPORT int ftw_sqlite_step(sqlite3_stmt *pStmt)
{
    return sqlite3_step(pStmt);
}

FTW_EXPORT int ftw_sqlite_finalize(sqlite3_stmt *pStmt)
{
    return sqlite3_finalize(pStmt);
}

FTW_EXPORT sqlite3_backup *ftw_sqlite_backup_init(sqlite3* pDestDb, const char *zDestDb, sqlite3* pSrcDb, const char *zSrcDb)
{
    return sqlite3_backup_init(pDestDb, zDestDb, pSrcDb, zSrcDb);
}

FTW_EXPORT int ftw_sqlite_backup_step(sqlite3_backup *p, int nPage)
{
    return sqlite3_backup_step(p, nPage);
}

FTW_EXPORT int ftw_sqlite_backup_finish(sqlite3_backup *p)
{
    return sqlite3_backup_finish(p);
}

FTW_EXPORT void ftw_sqlite_randomness(int N, void *pBuf)
{
    sqlite3_randomness(N, pBuf);
    return;
}
