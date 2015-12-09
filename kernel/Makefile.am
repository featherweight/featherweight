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
AUTOMAKE_OPTIONS = foreign no-installinfo no-dist no-installman

# Build submodule libraries first.
SUBDIRS = \
    jansson/upstream \
    nanomsg/upstream \
    pcre/upstream \
    .

# Featherweight currently does not have any m4 macros
# ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libftw.la

libftw_la_SOURCES = \
    jansson/ftw_json.c \
    nanomsg/ftw_nanomsg.c \
    pcre/ftw_pcre.c \
    sqlite/ftw_sqlite.c \
    ftw.c

libftw_la_LIBADD = \
    jansson/upstream/src/libjansson.la \
    nanomsg/upstream/libnanomsg.la \
    pcre/upstream/libpcre2-8.la

# TODO: better detection of this flag needed for nanomsg
#libftw_la_CPPFLAGS = -DNN_HAVE_OSX
libftw_la_CPPFLAGS = -DNN_HAVE_SEMAPHORE

# TODO: Linux vs OS X selection

libftw_la_LDFLAGS = \
    -version-info 1:0:0 \
    -LLVRTE_DIR \
    -l:liblvrt.so.14.0 \
    -no-undefined

#libftw_la_LDFLAGS = \
#    -version-info 1:0:0 \
#    -L/usr/local/natinst/labview \
#    -l:liblvrt.so.14.0 \
#    -no-undefined

#libftw_la_LDFLAGS = \
#    -version-info 1:0:0 \
#    -Wl,-F,/Library/Frameworks \
#    -Wl,-framework,"LabVIEW 14.0 Runtime" \
#    -no-undefined
