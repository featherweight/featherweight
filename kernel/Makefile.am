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

# libftw amalgamation

# Build submodule libraries first.
SUBDIRS = \
    jansson/upstream \
    jansson \
    nanomsg/upstream \
    nanomsg \
    pcre/upstream \
    pcre \
    sqlite

# Featherweight currently does not have any m4 macros
# ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libftw.la
libftw_la_SOURCES = ftw.c

libftw_la_LIBADD = \
    jansson/libftw_json.la \
    nanomsg/libftw_nanomsg.la \
    pcre/libftw_pcre.la \
    sqlite/libftw_sqlite.la

libftw_la_LDFLAGS = -L/usr/local/natinst/labview -l:liblvrt.so.13.0
