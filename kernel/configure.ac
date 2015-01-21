#
#    Copyright (c) 2014-2015 Wirebird Labs LLC. All rights reserved.
#
#    Permission is hereby granted, free of charge, to any person obtaining a copy
#    of this software and associated documentation files (the "Software"),
#    to deal in the Software without restriction, including without limitation
#    the rights to use, copy, modify, merge, publish, distribute, sublicense,
#    and/or sell copies of the Software, and to permit persons to whom
#    the Software is furnished to do so, subject to the following conditions:
#
#    The above copyright notice and this permission notice shall be included
#    in all copies or substantial portions of the Software.
#
#    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
#    IN THE SOFTWARE.
#

# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.69])

AC_INIT([ftw], [0.0.1], [featherweight.io])

AC_CONFIG_SRCDIR([ftw.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([.])

# Featherweight currently does not have any m4 macros
# AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.6 foreign -Wall])

# Checks for programs.
AC_PROG_CC
AM_PROG_AR

# Checks for libraries.
# Featherweight has no external dependencies!

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h])
AC_CHECK_HEADERS([float.h])
AC_CHECK_HEADERS([inttypes.h])
AC_CHECK_HEADERS([limits.h])
AC_CHECK_HEADERS([malloc.h])
AC_CHECK_HEADERS([stddef.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([string.h])
AC_CHECK_HEADERS([sys/file.h])
AC_CHECK_HEADERS([sys/mount.h])
AC_CHECK_HEADERS([sys/param.h])
AC_CHECK_HEADERS([sys/statvfs.h])
AC_CHECK_HEADERS([sys/time.h])
AC_CHECK_HEADERS([utime.h])

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
AC_CHECK_TYPES([ptrdiff_t])
AC_CHECK_MEMBERS([struct stat.st_blksize])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STRERROR_R
AC_CHECK_FUNCS([clock_gettime])
AC_CHECK_FUNCS([fdatasync])
AC_CHECK_FUNCS([getpagesize])
AC_CHECK_FUNCS([gettimeofday])
AC_CHECK_FUNCS([localtime_r])
AC_CHECK_FUNCS([memmove])
AC_CHECK_FUNCS([memset])
AC_CHECK_FUNCS([strerror])
AC_CHECK_FUNCS([strstr])
AC_CHECK_FUNCS([utime])

AC_CONFIG_FILES([Makefile])

Add additional submodules to this configuration
AC_CONFIG_SUBDIRS([
    jansson/upstream
    nanomsg/upstream
    pcre/upstream
])

LT_INIT
LT_OUTPUT

AC_OUTPUT
