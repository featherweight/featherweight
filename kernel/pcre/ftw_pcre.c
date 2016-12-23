/*
    Copyright (c) 2014-2016 Wirebird Labs LLC. All rights reserved.

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

#include "ftw_pcre.h"

static int ftw_pcre_callout(pcre2_callout_block *block, void *args);
FTW_PRIVATE_SUPPORT ftwrc resize_CalloutAccumulator(CalloutAccumulator ***arr, size_t elements);

MgErr ftw_pcre_version(LStrHandle version)
{
    ftwrc rc;
    char buf[1024];
    int sz;

    sz = pcre2_config(PCRE2_CONFIG_VERSION, buf);
    ftw_assert(sz <= sizeof(buf));

    rc = ftw_support_CStr_to_LStrHandle(&version, buf, sizeof(buf));

    return rc;
}

pcre2_code *ftw_pcre_compile(ConstLStrH regex, uint32_t options, LStrHandle err_string,
    int32 *err_offset_in_regex)
{
    pcre2_code *compiled_regex;
    PCRE2_SIZE err_offset;
    char buf[1024] = {0};
    int err_code;
    ftwrc lvrc;
    int rc;

    compiled_regex = pcre2_compile(LHStrBuf(regex), LHStrLen(regex), options, &err_code, &err_offset, NULL);

    if (compiled_regex) {
        return compiled_regex;
    }

    *err_offset_in_regex = (int32)err_offset;
    rc = pcre2_get_error_message(err_code, buf, sizeof(buf));
    ftw_assert (rc == StrLen(buf));
    lvrc = ftw_support_CStr_to_LStrHandle(&err_string, buf, sizeof(buf));

    return NULL;
}

ftwrc ftw_pcre_capture_groups(const pcre2_code *compiled_regex, LStrHandleArray **named_capturing_groups)
{
    uint32_t num_submatches;
    uint32_t namecount;
    uint32_t namesize;
    uint32_t entrysize;
    uChar *nametable;
    const uChar *offset;
    uInt16 submatch_index;
    uint32_t i;
    ftwrc rc;

    rc = pcre2_pattern_info(compiled_regex, PCRE2_INFO_NAMECOUNT, &namecount);
    if (rc)
        return rc;

    rc = pcre2_pattern_info(compiled_regex, PCRE2_INFO_NAMEENTRYSIZE, &entrysize);
    if (rc)
        return rc;

    rc = pcre2_pattern_info(compiled_regex, PCRE2_INFO_NAMETABLE, &nametable);
    if (rc)
        return rc;

    rc = pcre2_pattern_info(compiled_regex, PCRE2_INFO_CAPTURECOUNT, &num_submatches);
    if (rc)
        return rc;

    rc = ftw_support_expand_LStrHandleArray(&named_capturing_groups, num_submatches);
    if (rc)
        return rc;

    namesize = entrysize - sizeof(submatch_index);
    offset = nametable;

    for (i = 0; i < namecount; i++) {
        offset = nametable + i * entrysize;
        submatch_index = Word(offset[0], offset[1]) - 1;
        offset += sizeof(submatch_index);

        rc = ftw_support_CStr_to_LStrHandle(&((*named_capturing_groups)->element)[submatch_index], offset, namesize);
        if (rc)
            break;
    }

    return rc;
}

int32 ftw_pcre_match(const pcre2_code *compiled_regex, ConstLStrH subject,
    int32 startoffset, int32 *match_begin, int32 *match_end,
    int32Array **submatches, CalloutAccumulator **callout)
{
    struct ftw_callout_args arg;
    pcre2_match_context *ctx;
    pcre2_match_data *match_data;
    PCRE2_SIZE subj_len;
    PCRE2_SPTR subj_ptr;
    PCRE2_SIZE *ovector;
    uint32_t ovec_count;
    int num_submatches;
    ftwrc lvrc;
    int32 rc;
    int i;

    ctx = pcre2_match_context_create(NULL);
    if (ctx == NULL)
        return PCRE2_ERROR_INTERNAL;
    
    /*  Adjust these numbers to change characteristics of memory management. */
    arg.grow_size = 100;
    arg.accumulator = callout;
    arg.index = 0;

    rc = pcre2_set_callout(ctx, ftw_pcre_callout, &arg);
    if (rc) {
        pcre2_match_context_free(ctx);
        return rc;
    }

    subj_len = LHStrLen(subject);
    subj_ptr = LHStrBuf(subject);

    match_data = pcre2_match_data_create_from_pattern(compiled_regex, NULL);
    if (match_data == NULL) {
        pcre2_match_context_free(ctx);
        return PCRE2_ERROR_INTERNAL;
    }

    rc = pcre2_match(compiled_regex, subj_ptr, subj_len, (PCRE2_SIZE)startoffset, 0, match_data, ctx);

    /*  Sanity check array size.  */
    ftw_assert(arg.index >= 0 && (*arg.accumulator)->dimsize >= 0);

    /*  This should always be a trim operation, and never an increase.  */
    ftw_assert(arg.index <= (*arg.accumulator)->dimsize);

    /*  Trim callout buffer. */
    lvrc = resize_CalloutAccumulator(&callout, arg.index);
    if (lvrc) {
        rc = PCRE2_ERROR_INTERNAL;
        goto MATCH_DONE;
    }

    if (rc < 0) {
        /*  No match was found, or an error encountered. */
        *match_begin = PCRE2_ERROR_NOMATCH;
        *match_end = PCRE2_ERROR_NOMATCH;
        goto MATCH_DONE;
    }

    /*  Retrieve match data. */
    ovec_count = pcre2_get_ovector_count(match_data);
    ftw_assert(ovec_count > 0);
    ovector = pcre2_get_ovector_pointer(match_data);
    ftw_assert(ovector);

    /*  A whole match was found, but no submatches. */
    *match_begin = (int32)ovector[0];
    *match_end = (int32)ovector[1];

    /*  Resize the submatch buffer, accounting for the first ovec as the whole match.  */
    num_submatches = (int)ovec_count - 1;
    if (num_submatches == 0) {
        goto MATCH_DONE;
    }
    lvrc = ftw_support_expand_int32Array(&submatches, num_submatches * 2);
    if (lvrc) {
        rc = PCRE2_ERROR_INTERNAL;
        goto MATCH_DONE;
    }

    for (i = 0; i < num_submatches; i++) {
        /*  Advance to next submatch pair. */
        ovector += 2;
        (*submatches)->element[2 * i] = ovector[0];
        (*submatches)->element[2 * i + 1] = ovector[1];
    }

MATCH_DONE:
    pcre2_match_data_free(match_data);
    pcre2_match_context_free(ctx);
    return rc;
}

void ftw_pcre_free(pcre2_code *compiled_regex)
{
    if (compiled_regex)
        pcre2_code_free(compiled_regex);
}

int ftw_pcre_callout(pcre2_callout_block *block, void *args)
{
    struct ftw_callout_args *arg;
    int32_t new_dim_size;
    MgErr lvrc;

    ftw_assert(block && args);

    /*  Expected current version of the callout block. */
    ftw_assert(block->version == 1);

    arg = (struct ftw_callout_args *)args;

    /*  Allow this to grow indefinitely. Overflow would return error. */
    if (arg->index >= (*(arg->accumulator))->dimsize) {
        new_dim_size = ((*(arg->accumulator))->dimsize + arg->grow_size);
        lvrc = resize_CalloutAccumulator(&arg->accumulator, new_dim_size);
        if (lvrc) {
            return PCRE2_ERROR_INTERNAL;
        }
    }

    (*(arg->accumulator))->element[arg->index].callout_id = block->callout_number;
    (*(arg->accumulator))->element[arg->index].subject_current_pos = block->current_position;
    (*(arg->accumulator))->element[arg->index].subject_start_match_pos = block->start_match;
    (*(arg->accumulator))->element[arg->index].capture_top = block->capture_top;
    (*(arg->accumulator))->element[arg->index].capture_last = block->capture_last;
    (*(arg->accumulator))->element[arg->index].pattern_position = block->pattern_position;
    (*(arg->accumulator))->element[arg->index].callout_name_offset = block->callout_string_offset;
    (*(arg->accumulator))->element[arg->index].callout_name_length = block->callout_string_length;

    arg->index++;

    return 0;
}


ftwrc resize_CalloutAccumulator(CalloutAccumulator ***arr, size_t elements)
{
    MgErr lvrc;
    size_t sz;

    if (arr == NULL || *arr == NULL || **arr == NULL) {
        return EFTWARG;
    }

    FTW_COMPILER_ASSERT(sizeof(struct ftw_pcre_callout_data) == 8 * sizeof(int32));
    FTW_COMPILER_ASSERT(sizeof(CalloutAccumulator) == sizeof(int32) + sizeof(struct ftw_pcre_callout_data));
    FTW_COMPILER_ASSERT(Offset(CalloutAccumulator, element) == 4);
    sz = Offset(CalloutAccumulator, element) + sizeof(struct ftw_pcre_callout_data) * elements;
    lvrc = DSSetHandleSize(*arr, sz);
    if (lvrc) {
        return ELVMGRBASE + lvrc;
    }
    
    (**arr)->dimsize = (int32)elements;

    return EFTWOK;
}
