#
#    Copyright (c) 2014-2016 Wirebird Labs LLC. All rights reserved.
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

cmake_minimum_required (VERSION 2.8.12)

project (featherweight C)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

# Ensures that we do an out of source build
string (COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" insource)
get_filename_component (PARENTDIR ${CMAKE_SOURCE_DIR} PATH)
string (COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${PARENTDIR}" insourcesubdir)
if (insource OR insourcesubdir)
    message (FATAL_ERROR "${CMAKE_PROJECT_NAME} requires an out of source build.")
endif ()

enable_testing ()

set (JANSSON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/jansson/upstream")
set (NANOMSG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/nanomsg/upstream")
set (PCRE2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/pcre/upstream")
set (LIBUV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libuv")

### Jansson
set (JANSSON_BUILD_DOCS OFF CACHE BOOL "Featherweight skips building the Jansson documentation.")
set (JANSSON_EXAMPLES OFF CACHE BOOL "Featherweight skips building the Jansson examples.")
set (JANSSON_BUILD_SHARED_LIBS OFF CACHE BOOL "Featherweight skips building a Jansson shared library.")
add_subdirectory (${JANSSON_DIR} ${JANSSON_DIR}/build)

### libuv
add_subdirectory (${LIBUV_DIR} ${LIBUV_DIR}/build)

### PCRE2
set (PCRE2_SUPPORT_PCREGREP_JIT OFF CACHE BOOL "Featherweight skips building Just-in-time compiling in pcregrep.")
add_subdirectory (${PCRE2_DIR} ${PCRE2_DIR}/build)

# The rigor of test #2 requires special compiler/linker settings:
if (MSVC)
    # According to http://www.pcre.org/current/doc/html/NON-AUTOTOOLS-BUILD.txt
    # 8MB is required; however PCRE2 is observed to need 16MB to pass this test.
    set_target_properties (pcre2test PROPERTIES LINK_FLAGS "/STACK:0x1000000")
elseif (CMAKE_C_COMPILER_ID MATCHES "Clang")
    # Discussion on this topic: http://comments.gmane.org/gmane.comp.lang.pcre.devel/3809
    target_compile_options (pcre2-8 PUBLIC -O3)
endif ()

### nanomsg
set (WS_AUTOBAHN_TESTS ON CACHE BOOL "Opt-in to Autobahn WebSocket tests.")
set (NN_STATIC_LIB ON CACHE BOOL "Include as part of amalgamation.")
set (NN_ENABLE_DOC OFF CACHE BOOL "Turn off documentation.")
add_subdirectory (${NANOMSG_DIR} ${NANOMSG_DIR}/build)

### SQLite
    # SQLite has no CMakeLists.txt, hence no need for this section.
    # The SQLite amalgamation is included directly in ftw_sqlite.h

### featherweight amalgamation
set (FTW_SRC_FILES
    ftw.h
    ftw.c
    ftw_libuv.h
    ftw_libuv.c
    framework/ftw_framework.h
    framework/ftw_framework.c
    jansson/ftw_json.h
    jansson/ftw_json.c
    nanomsg/ftw_nanomsg.h
    nanomsg/ftw_nanomsg.c
    pcre/ftw_pcre.h
    pcre/ftw_pcre.c
    sqlite/ftw_sqlite.h
    sqlite/ftw_sqlite.c
)

add_library (${CMAKE_PROJECT_NAME} SHARED ${FTW_SRC_FILES})

target_link_libraries (${CMAKE_PROJECT_NAME} jansson)
target_link_libraries (${CMAKE_PROJECT_NAME} pcre2-8)
target_link_libraries (${CMAKE_PROJECT_NAME} nanomsg)
target_link_libraries (${CMAKE_PROJECT_NAME} libuv)

target_compile_options (${CMAKE_PROJECT_NAME} PUBLIC -DSQLITE_ENABLE_JSON1)


set (LVRTE_INCLUDE "${FTW_LVIDE_PATH}/cintools")
if (WIN32)
    find_library (LVRTE_LIBRARY labviewv PATHS "${LVRTE_INCLUDE}" NO_DEFAULT_PATH)
    set (FTW_LIB_DESTINATION "")
    set_target_properties (${CMAKE_PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_debug")
    set_target_properties (${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "../lib")
    set_target_properties (${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "../lib")
    set_target_properties (${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "../lib")
    set_target_properties (${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "../lib")
    if (CMAKE_SIZEOF_VOID_P EQUAL "8")
        set_target_properties (${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME "ftw64")
    elseif ("${CMAKE_SIZEOF_VOID_P}" EQUAL "4")
        set_target_properties (${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME "ftw32")
    else ()
        message (FATAL_ERROR "${CMAKE_PROJECT_NAME} could not detect Windows bitness.")
    endif ()
elseif (APPLE)
    set (LVRTE_LIBRARY "/Library/Frameworks/LabVIEW 15.0 Runtime")
    set (FTW_LIB_DESTINATION "")
    set_target_properties (${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME "ftw")
## this is the best-known heuristic for detecting a build on NI Linux RT
elseif (CMAKE_SYSTEM MATCHES "^Linux-.*-ni-.*$")
    find_library (LVRTE_LIBRARY liblvrt.so.15.0 PATHS /usr/local/natinst/labview NO_DEFAULT_PATH)
    execute_process (COMMAND readlink -f ${LVRTE_LIBRARY})
    set (FTW_LIB_DESTINATION "/usr/lib")
    set_target_properties (${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME "ftw")
elseif (UNIX)
    find_library (LVRTE_LIBRARY lvrtdark PATHS ${CMAKE_CURRENT_SOURCE_DIR}/download-cache/ NO_DEFAULT_PATH)
    execute_process (COMMAND readlink -f ${LVRTE_LIBRARY})
    set (FTW_LIB_DESTINATION "")
    set_target_properties (${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME "ftw")
else ()
    message (FATAL_ERROR "Unreachable.")
endif ()

# Add links to the LabVIEW Runtime Engine
message (STATUS "LV Library linked: ${LVRTE_LIBRARY}")
target_link_libraries (${CMAKE_PROJECT_NAME} "${LVRTE_LIBRARY}")
message (STATUS "LV Headers: ${LVRTE_INCLUDE}")
target_include_directories (${CMAKE_PROJECT_NAME} PUBLIC "${LVRTE_INCLUDE}")

if (MSVC)
    # This is required for 'Visual Studio 12' and higher, apparently because
    # labviewv.lib as of LV2013 is compiled without safe exception handlers.
    set_target_properties (${CMAKE_PROJECT_NAME} PROPERTIES LINK_FLAGS "/SAFESEH:NO")
endif ()

# Link to headers generated by the CMake build.
get_target_property (JANSSON_INCLUDE_DIRS jansson INCLUDE_DIRECTORIES)
include_directories (${JANSSON_INCLUDE_DIRS})

# Ensuring amalgamation compiles with same compiler flags as components
get_directory_property (NANOMSG_COMPILE_DEFS DIRECTORY ${NANOMSG_DIR}\\src COMPILE_DEFINITIONS)
message (STATUS "nanomsg compile definitions: ${NANOMSG_COMPILE_DEFS}")
get_directory_property (LIBUV_COMPILE_DEFS DIRECTORY ${LIBUV_DIR} COMPILE_DEFINITIONS)
message (STATUS "libuv compile definitions: ${LIBUV_COMPILE_DEFS}")
set (FTW_COMPILE_DEFS ${NANOMSG_COMPILE_DEFS} ${LIBUV_COMPILE_DEFS})
target_compile_definitions (${CMAKE_PROJECT_NAME} PUBLIC ${FTW_COMPILE_DEFS})

if (NOT FTW_LIB_DESTINATION STREQUAL "")
    message (STATUS "Installing FTW to this system path: ${FTW_LIB_DESTINATION}")
    install (TARGETS ${CMAKE_PROJECT_NAME} LIBRARY DESTINATION ${FTW_LIB_DESTINATION})
else ()
    message (STATUS "FTW Kernel is not automatically installed to a system path on this platform.")
endif ()
