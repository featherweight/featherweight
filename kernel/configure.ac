#
#  Copyright (c) 2014-2015 Wirebird Labs LLC. All rights reserved.
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom
#  the Software is furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included
#  in all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
#  IN THE SOFTWARE.
#

# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([ftw], [0.0.1], [featherweight.io])
AC_CONFIG_SRCDIR([ftw.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# Featherweight has no external dependencies!

# Checks for header files.
AC_CHECK_HEADERS
  ([
    fcntl.h
    float.h
    inttypes.h
    limits.h
    malloc.h
    stddef.h
    stdint.h
    stdlib.h
    string.h
    sys/file.h
    sys/ioctl.h
    sys/mount.h
    sys/param.h
    sys/statvfs.h
    sys/time.h
    unistd.h
    utime.h
  ])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UID_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

AC_CHECK_MEMBERS
  ([
    struct stat.st_blksize
  ])

AC_CHECK_TYPES
  ([
    ptrdiff_t
  ])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STRERROR_R
AC_CHECK_FUNCS
  ([
    clock_gettime
    fdatasync
    getpagesize
    gettimeofday
    localtime_r
    memmove
    memset
    strerror
    strstr
    utime
  ])

AC_CONFIG_FILES
  ([
    Makefile
  ])

# Add additional submodules to this configuration
AC_CONFIG_SUBDIRS
  ([
    jansson/upstream
    nanomsg/upstream
    pcre/upstream
  ])

AC_OUTPUT
