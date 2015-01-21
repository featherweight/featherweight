# Build submodule libraries first.
SUBDIRS = jansson/upstream

# Featherweight currently does not have any m4 macros
# ACLOCAL_AMFLAGS = -I m4

# Include submodule headers when compiling featherweight
AM_CPPFLAGS = -I$(srcdir)/jansson/upstream

lib_LTLIBRARIES = libftw.la
libftw_la_SOURCES = ftw.c jansson/ftw_json.c

libftw_la_LIBADD = jansson/upstream/src/libjansson.la
libftw_la_LDFLAGS = -L/usr/local/natinst/labview -l:liblvrt.so.13.0
