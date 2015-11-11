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

#include "ftw_pcre.h"

static int ftw_pcre_callout(pcre_callout_block *callout_data);

const char *ftw_pcre_version(void)
{
    return pcre_version();
}

pcre *ftw_pcre_compile(const char *regex, int options, LStrHandle error_string,
    int32_t *error_offset_in_regex)
{
    pcre *compiled_regex;
    const char *err;

    pcre_callout = ftw_pcre_callout;

    compiled_regex = pcre_compile(regex, options, &err, error_offset_in_regex, NULL);

    if (compiled_regex == NULL) {
        ftw_support_buffer_to_LStrHandle(&error_string, err, StrLen ((const uChar *)err));
        return NULL;
    }

    return compiled_regex;
}

int32_t ftw_pcre_capture_groups(const pcre *compiled_regex, LStrHandleArray **capture_groups)
{
    int i;
    int rc;
    int namecount;
    int namesize;
    int num_submatches;
    uChar *nametable;
    const uChar *offset;
    MgErr lv_err;
    size_t buf_size;
    size_t name_len;
    uInt16 submatch_index;
    LStrHandle element;

    rc = pcre_fullinfo(compiled_regex, NULL, PCRE_INFO_NAMECOUNT, &namecount);
    if (rc)
        return rc;

    rc = pcre_fullinfo(compiled_regex, NULL, PCRE_INFO_NAMEENTRYSIZE, &namesize);
    if (rc)
        return rc;

    rc = pcre_fullinfo(compiled_regex, NULL, PCRE_INFO_NAMETABLE, &nametable);
    if (rc)
        return rc;

    rc = pcre_fullinfo(compiled_regex, NULL, PCRE_INFO_CAPTURECOUNT, &num_submatches);
    if (rc)
        return rc;

    buf_size = Offset(LStrHandleArray, element) + sizeof(LStrHandle) * num_submatches;
    lv_err = DSSetHSzClr(capture_groups, buf_size);

    if (lv_err != mgNoErr)
        return -lv_err;

    (*capture_groups)->dimsize = num_submatches;

    for (i = 0; i < namecount; i++) {
        offset = nametable + i * namesize;
        submatch_index = Word(*(offset + 0), *(offset + 1)) - 1;
        offset += sizeof(submatch_index);

        name_len = StrLen(offset);
        buf_size = Offset(LStr, str) + name_len;
        element = (LStrHandle)DSNewHandle(buf_size);
        ftw_assert(element);

        ((*capture_groups)->element)[submatch_index] = element;
        (*element)->cnt = name_len;
        MoveBlock(offset, (*element)->str, name_len);
    }

    return num_submatches;
}

intptr_t ftw_pcre_exec(const pcre *compiled_regex, const LStrHandle subject,
    int32_t startoffset, int32_t options, int32_t *match_begin, int32_t *match_end,
    I32Array **submatch_buffer, CalloutAccumulator **callout)
{
    int rc;
    int max_rc;
    int subj_len;
    const char *subj_ptr;
    size_t sz;
    size_t num_submatches;
    pcre_extra extra;
    MgErr lv_err;
    struct ftw_callout_args arg;

    arg.accumulator = callout;
    arg.index = 0;

    extra.flags = PCRE_EXTRA_CALLOUT_DATA;
    extra.callout_data = &arg;

    subj_len = LHStrLen(subject);
    subj_ptr = (const char *)LHStrBuf(subject);

    /*  Adjust these numbers to change characteristics of memory management. */
    arg.num_elements_increment = 100;

    /* As per http://www.pcre.org/pcre.txt, ovector size of submatches is only 2/3 used for matches. */
    max_rc = ((*submatch_buffer)->dimsize * 2) / 3;

    rc = pcre_exec(compiled_regex, &extra, subj_ptr, subj_len, startoffset,
        options, (*submatch_buffer)->element, (*submatch_buffer)->dimsize);

    /*  Sanity check return value.  */
    ftw_assert(rc <= max_rc);

    /*  Sanity check array size.  */
    assert(arg.index >= 0 && (*arg.accumulator)->dimsize >= 0);

    /*  This should always be a trim operation, and never an increase.  */
    assert(arg.index <= (*arg.accumulator)->dimsize);

    /*  Resize callout buffer. */
    sz = Offset(CalloutAccumulator, element) + sizeof(struct ftw_pcre_callout_data) * arg.index;
    lv_err = DSSetHSzClr(callout, sz);
    if (lv_err != mgNoErr)
        return PCRE_ERROR_INTERNAL;
    (*callout)->dimsize = arg.index;

    if (rc <= 0) {
        /*  No match was found, or an error encountered. */
        *match_begin = PCRE_ERROR_NOMATCH;
        *match_end = PCRE_ERROR_NOMATCH;
        num_submatches = 0;
        sz = Offset(I32Array, element);
    }
    else {
        /*  Peel first two values as the whole match. */
        *match_begin = (*submatch_buffer)->element[0];
        *match_end = (*submatch_buffer)->element[1];

        /*  Multiply by two, since array is begin/end pair. */
        num_submatches = (rc - 1) * 2;
        sz = sizeof(int32_t) * num_submatches * 2;

        /*  Shift array to  account for first two indices of whole match. */
        MoveBlock(&((*submatch_buffer)->element[2]), &((*submatch_buffer)->element[0]), sz);
        sz += Offset(I32Array, element);
    }

    lv_err = DSSetHSzClr(submatch_buffer, sz);
    if (lv_err != mgNoErr)
        return PCRE_ERROR_INTERNAL;
    (*submatch_buffer)->dimsize = num_submatches;

    return rc;
}

static int ftw_pcre_callout(pcre_callout_block *data)
{
    struct ftw_callout_args *arg;
    int32_t new_dim_size;
    size_t callout_size;
    MgErr lv_err;

    /*  Expected current version of the callout block. */
    assert(data->version == 2);

    arg = (struct ftw_callout_args*)(data->callout_data);

    /*  Allow this to grow indefinitely. Overflow would return error. */
    if (arg->index >= (*(arg->accumulator))->dimsize) {
        new_dim_size = ((*(arg->accumulator))->dimsize + arg->num_elements_increment);
        callout_size = Offset(CalloutAccumulator, element) + sizeof(struct ftw_pcre_callout_data) * new_dim_size;
        lv_err = DSSetHSzClr(arg->accumulator, callout_size);
        if (lv_err != mgNoErr) {
            return PCRE_ERROR_INTERNAL;
        }
        (*(arg->accumulator))->dimsize = new_dim_size;
    }

    (*(arg->accumulator))->element[arg->index].callout_id = data->callout_number;
    (*(arg->accumulator))->element[arg->index].subject_current_pos = data->current_position;
    (*(arg->accumulator))->element[arg->index].subject_start_match_pos = data->start_match;
    (*(arg->accumulator))->element[arg->index].capture_top = data->capture_top;
    (*(arg->accumulator))->element[arg->index].capture_last = data->capture_last;
    (*(arg->accumulator))->element[arg->index].pattern_position = data->pattern_position;

    arg->index++;

    return 0;
}

void ftw_pcre_free(pcre *compiled_regex)
{
    if (compiled_regex)
        pcre_free(compiled_regex);
}
