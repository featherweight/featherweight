#include "ftw_pcre.h"

static int ftw_pcre_callout(pcre_callout_block *callout_data);

char *ftw_pcre_version(void)
{
    return pcre_version();
}

static MgErr ftw_support_copy_to_LStrHandle(LStrHandle dest, const void *src, size_t length)
{
    MgErr resize_err;

    resize_err = NumericArrayResize(uB, 1, (UHandle *)&dest, length);
    if (resize_err == mgNoErr) {
        MoveBlock(src, LHStrBuf(dest), length);
        LStrLen(*dest) = length;
    }
    return resize_err;
}

pcre *ftw_pcre_compile(const char *regex, int options, LStrHandle error_string,
    int *error_offset_in_regex, LStrHandleArray **named_capturing_groups)
{
    pcre *compiled_regex;
    char *err;
    int namecount;
    int num_submatches;
    int namesize;
    int i;
    const uChar *offset;
    LStrHandle element;
    size_t buf_size;
    size_t name_len;
    uChar *nametable;
    uInt16 submatch_index;
    MgErr lv_err;

    pcre_callout = ftw_pcre_callout;

    compiled_regex = pcre_compile(regex, options, &err, error_offset_in_regex, NULL);

    if (compiled_regex == NULL) {
        ftw_support_copy_to_LStrHandle(error_string, err, StrLen (err));
        return NULL;
    }

    if (pcre_fullinfo(compiled_regex, NULL, PCRE_INFO_NAMECOUNT, &namecount))
        return NULL;
    if (pcre_fullinfo(compiled_regex, NULL, PCRE_INFO_NAMEENTRYSIZE, &namesize))
        return NULL;
    if (pcre_fullinfo(compiled_regex, NULL, PCRE_INFO_NAMETABLE, &nametable))
        return NULL;
    if (pcre_fullinfo(compiled_regex, NULL, PCRE_INFO_CAPTURECOUNT, &num_submatches))
        return NULL;

    buf_size = Offset(LStrHandleArray, element) + sizeof(LStrHandle) * num_submatches;
    lv_err = DSSetHSzClr(named_capturing_groups, buf_size);

    if (lv_err != mgNoErr) {
        err = "LabVIEW unable to allocate enough memory.";
        ftw_support_copy_to_LStrHandle(error_string, err, StrLen(err));
        return NULL;
    }

    /*  Return early if no submatches. */
    if (num_submatches == 0)
        return compiled_regex;

    (*named_capturing_groups)->dimsize = num_submatches;

    for (i = 0; i < namecount; i++) {
        offset = nametable + i * namesize;
        submatch_index = Word(*(offset + 0), *(offset + 1)) - 1;
        offset += sizeof(submatch_index);

        name_len = StrLen(offset);
        buf_size = Offset(LStr, str) + name_len;
        element = (LStrHandle)DSNewHandle(buf_size);
        assert(element);

        ((*named_capturing_groups)->element)[submatch_index] = element;
        (*element)->cnt = name_len;
        MoveBlock(offset, (*element)->str, name_len);
    }

    return compiled_regex;
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
    subj_ptr = LHStrBuf(subject);

    /*  Adjust these numbers to change characteristics of memory management. */
    arg.num_elements_increment = 100;

    /* As per http://www.pcre.org/pcre.txt, ovector size of submatches is only 2/3 used for matches. */
    max_rc = ((*submatch_buffer)->dimsize * 2) / 3;

    rc = pcre_exec(compiled_regex, &extra, subj_ptr, subj_len, startoffset,
        options, (*submatch_buffer)->element, (*submatch_buffer)->dimsize);

    /*  Sanity check return value.  */
    assert(rc <= max_rc);

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
        sz = sizeof(int32_t) * num_submatches;

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
