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

cmake_minimum_required (VERSION 2.8.12)
include (CheckIncludeFiles)
include (CheckSymbolExists)
include (CheckCSourceCompiles)

project (featherweight C)

set (CMAKE_VERBOSE_MAKEFILE ON)

# Print all variables for debug
get_cmake_property (_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    message (STATUS "${_variableName}=${${_variableName}}")
endforeach ()

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

### Jansson
    set (JANSSON_BUILD_DOCS OFF CACHE BOOL "Featherweight skips building the Jansson documentation.")
    set (JANSSON_EXAMPLES OFF CACHE BOOL "Featherweight skips building the Jansson examples.")
    add_subdirectory (${JANSSON_DIR} ${JANSSON_DIR}/build)

### PCRE2
    set (PCRE2_SUPPORT_PCREGREP_JIT OFF CACHE BOOL "Featherweight skips building Just-in-time compiling in pcregrep.")
    add_subdirectory (${PCRE2_DIR} ${PCRE2_DIR}/build)

    # Unit test #2 provides guidance to increase the stack size to 8MB,
    # however PCRE2 is observed to need 16MB to pass this test.
    # Remove this line to observe test failure with RUN_TESTS in MSVC.
    if (MSVC)
        set_target_properties(pcre2test PROPERTIES LINK_FLAGS "/STACK:16000000")
    endif ()

### nanomsg
    set (WS_AUTOBAHN_TESTS ON CACHE BOOL "Opt-in to Autobahn WebSocket tests.")
    set (NN_STATIC_LIB ON CACHE BOOL "Include as part of amalgamation.")
    add_subdirectory (${NANOMSG_DIR} ${NANOMSG_DIR}/build)

    #  Build chain settings, and suppress exporting nanomsg functions (since library functionality is curated and exported as ftw-nanomsg functions).
    # set (NANOMSG_COMPILE_DEFS -DNN_NO_EXPORTS)

    # get_target_property (NANOMSG_SRC_FILES_TMP nanomsg SOURCES)
    # get_target_property (NANOMSG_LINK_LIBS nanomsg LINK_LIBRARIES)

    # set (NANOMSG_SRC_DIR "${NANOMSG_DIR}/src")

    # Provide same folder structure in MSVC project as on disk
    # foreach (f ${NANOMSG_SRC_FILES_TMP})
    #     # Get the path of the file relative to source directory
    #     if (IS_ABSOLUTE "${f}")
    #         file (RELATIVE_PATH f ${NANOMSG_SRC_DIR} ${f})
    #     endif ()
    #     set (SRC_GROUP "${f}")
    #     set (f "${NANOMSG_SRC_DIR}/${f}")
    #
    #     # Remove the filename part
    #     string (REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRC_GROUP ${SRC_GROUP})
    #
    #     # CMake source_group expects \\, not /
    #     string (REPLACE / \\ SRC_GROUP ${SRC_GROUP})
    #     source_group ("${SRC_GROUP}" FILES ${f})
    #
    #     list (APPEND NANOMSG_SRC_FILES ${f})
    #     #message( STATUS "${SRC_GROUP} -- ${f}")
    # endforeach ()

    # add_library (ftwnanomsg STATIC ${NANOMSG_SRC_FILES})
    # target_compile_definitions (ftwnanomsg PUBLIC ${NANOMSG_COMPILE_DEFS})
    # target_link_libraries (ftwnanomsg ${NANOMSG_LINK_LIBS})

### SQLite
    # SQLite has no CMakeLists.txt, hence no need for this section.
    # The SQLite amalgamation is included directly in ftw_sqlite.h

### featherweight amalgamation
    set (FTW_SRC_FILES
        ftw.h
        ftw.c
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

    # Add links to the LabVIEW Runtime Engine
    if (Win32)
        target_link_libraries (${CMAKE_PROJECT_NAME} ../labview/labviewv)
    elseif (APPLE)
        target_link_libraries (${CMAKE_PROJECT_NAME} "/Library/Frameworks/LabVIEW 14.0 Runtime")
    elseif (UNIX)
        target_link_libraries (${CMAKE_PROJECT_NAME} liblvrtdark.so)
    else ()
        message (FATAL_ERROR "Unreachable.")
    endif ()

    # Name the output library
    if (Win32)
      if ("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
        set_target_properties ("${CMAKE_PROJECT_NAME}" PROPERTIES OUTPUT_NAME "ftw64")
      elseif ("${CMAKE_SIZEOF_VOID_P}" EQUAL "4")
        set_target_properties ("${CMAKE_PROJECT_NAME}" PROPERTIES OUTPUT_NAME "ftw32")
      else ()
        message (FATAL_ERROR "${CMAKE_PROJECT_NAME} could not detect Windows bitness.")
      endif ()
    else ()
      set_target_properties ("${CMAKE_PROJECT_NAME}" PROPERTIES OUTPUT_NAME "libftw")
    endif ()

    if (MSVC)
        # This is required for 'Visual Studio 12' and higher, apparently because
        # labviewv.lib as of LV2013 is compiled without safe exception handlers.
        set_target_properties ("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SAFESEH:NO")
    endif ()

    # Link to headers generated by the CMake build.
    get_target_property (JANSSON_INCLUDE_DIRS jansson INCLUDE_DIRECTORIES)
    include_directories (${JANSSON_INCLUDE_DIRS})

    # Ensuring amalgamation compiles with same compiler flags as components
    get_target_property (NANOMSG_COMPILE_DEFS nanomsg COMPILE_DEFINITIONS)
    target_compile_definitions ("${CMAKE_PROJECT_NAME}" PUBLIC ${NANOMSG_COMPILE_DEFS})
