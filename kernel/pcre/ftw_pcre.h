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

#ifndef FTW_PCRE_H_INCLUDED
#define FTW_PCRE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define PCRE2_CODE_UNIT_WIDTH 8

#include "../ftw.h"
#include "upstream/src/config.h"
#include "upstream/src/pcre2.h"

/*  FTW-PCRE types. */
struct ftw_pcre_callout_data {
    int32 callout_id;
    int32 subject_current_pos;
    int32 subject_start_match_pos;
    int32 capture_top;
    int32 capture_last;
    int32 pattern_position;
    int32 callout_name_offset;
    int32 callout_name_length;
};

typedef struct {
    int32 dimsize;
    struct ftw_pcre_callout_data element[1];
} CalloutAccumulator;

struct ftw_callout_args {

    /*  Buffer that stores an array of callback data. */
    CalloutAccumulator **accumulator;

    /*  Current write position into the callback array. */
    int32 index;

    /*  Change these parameters to control how the accumulator grows. */
    int32 grow_size;
};

/*  FTW-PCRE exported functions. */
FTW_EXPORT MgErr ftw_pcre_version(LStrHandle version);

FTW_EXPORT pcre2_code *ftw_pcre_compile(ConstLStrH regex, uint32_t options, LStrHandle err_string,
    int32 *err_offset_in_regex);

FTW_EXPORT ftwrc ftw_pcre_capture_groups(const pcre2_code *compiled_regex,
    LStrHandleArray **named_capturing_groups);

FTW_EXPORT int32 ftw_pcre_match(const pcre2_code *compiled_regex, ConstLStrH subject,
    int32 startoffset, int32 *match_begin, int32 *match_end,
    int32Array **submatches, CalloutAccumulator **callout);

FTW_EXPORT void ftw_pcre_free(pcre2_code *compiled_regex);

#ifdef __cplusplus
}
#endif

#endif
