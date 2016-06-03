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

#include "ftw_libuv.h"

MgErr ftw_libuv_version(LStrHandle version)
{
    MgErr lv_err;

    lv_err = ftw_support_CStr_to_LStrHandle(&version, uv_version_string(), 1024);

    return lv_err;
}

MgErr ftw_libuv_error(int *err_number, LStrHandle error_name, LStrHandle error_message)
{
    MgErr lv_err;

    lv_err = ftw_support_CStr_to_LStrHandle (&error_name, uv_err_name (*err_number), 1024);
    if (lv_err) {
        return lv_err;
    }

    lv_err = ftw_support_CStr_to_LStrHandle (&error_message, uv_strerror (*err_number), 1024);


    return lv_err;
}

FTW_PRIVATE_SUPPORT void ftw_libuv_callback_process_exit (uv_process_t *proc, int64_t exit_status, int term_signal)
{
    ftw_assert(proc->data);
    *(((struct ftw_libuv_process *) (proc->data))->exit_code) = exit_status;
    *(((struct ftw_libuv_process *) (proc->data))->signal) = term_signal;
    uv_close((uv_handle_t*) proc, NULL);
}

FTW_PRIVATE_SUPPORT void ftw_libuv_callback_alloc (uv_handle_t *handle, size_t suggested_size, uv_buf_t* buf)
{
    LStrHandle lv_mem;

    lv_mem = (LStrHandle) DSNewHandle(sizeof (int32) + suggested_size * sizeof (uChar));

    if (lv_mem) {
        LHStrPtr (lv_mem)->cnt = (int32) suggested_size;
        *buf = uv_buf_init(LHStrBuf(lv_mem), suggested_size);
    }
    else {
        *buf = uv_buf_init(NULL, 0);
    }
    return;
}

FTW_PRIVATE_SUPPORT void ftw_libuv_callback_read_pipe (uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
    struct ftw_libuv_stream *context;
    LStrHandle message;
    MgErr lv_err;

    /*  Preconditions expected of FTW. */
    ftw_assert(stream->data);

    message = ftw_recover_LStrHandle (buf->base);

    /*  This is analogous to EAGAIN; silently dispose unused buffer. */
    if (nread <= 0) {
        if (nread == UV_EOF) {
            uv_close ((uv_handle_t *) stream, NULL);
        }

        if (message) {
            lv_err = DSDisposeHandle (message);
            ftw_assert (lv_err == mgNoErr);
        }
        return;
    }

    context = stream->data;

    LHStrPtr (message)->cnt = (int32) nread;

    lv_err = PostLVUserEvent(*(context->msg_to_lv_event), &message);

    lv_err = DSDisposeHandle (message);

    ftw_assert (lv_err == mgNoErr);
}

int ftw_libuv_spawn_process(struct ftw_libuv_callsite **callsite, LVUserEventRef *lv_event,
    char *exe, char *cmd, int64_t *exit_code, int64_t *signal)
{
    int rc;
    char *args [3];
    uv_loop_t loop;
    uv_pipe_t stdout_pipe;
    uv_pipe_t stderr_pipe;
    uv_process_t new_process;
    uv_process_options_t opts = {0};
    uv_stdio_container_t iostreams [3];
    struct ftw_libuv_process proc_data = {0};
    struct ftw_libuv_stream context;

    /*  Preconditions expected of LabVIEW. */
    ftw_assert(callsite && *callsite && lv_event && cmd);

    rc = uv_loop_init(&loop);
    if (rc) {
        return rc;
    }

    args[0] = exe;
    args[1] = cmd;
    args[2] = NULL;

    proc_data.exit_code = exit_code;
    proc_data.signal = signal;
    new_process.data = &proc_data;
    context.msg_to_lv_event = lv_event;
    stdout_pipe.data = &context;
    stderr_pipe.data = &context;

    rc = uv_pipe_init(&loop, &stdout_pipe, 0);
    if (rc) {
        uv_loop_close(&loop);
        return rc;
    }

    rc = uv_pipe_init(&loop, &stderr_pipe, 0);
    if (rc) {
        uv_loop_close(&loop);
        return rc;
    }

    opts.stdio_count = 3;
    opts.stdio = iostreams;
    opts.stdio[0].flags = UV_IGNORE;
    opts.stdio[1].flags = UV_CREATE_PIPE | UV_WRITABLE_PIPE;
    opts.stdio[1].data.stream = (uv_stream_t *) &stdout_pipe;
    opts.stdio[2].flags = UV_CREATE_PIPE | UV_WRITABLE_PIPE;
    opts.stdio[2].data.stream = (uv_stream_t *) &stderr_pipe;
    //opts.stdio[2].flags = UV_IGNORE;
    
    opts.file = exe;
    opts.args = args;
    opts.exit_cb = ftw_libuv_callback_process_exit;

    rc = uv_spawn(&loop, &new_process, &opts);
    if (rc) {
        uv_loop_close(&loop);
        return rc;
    }

    rc = uv_read_start((uv_stream_t*) &stdout_pipe, ftw_libuv_callback_alloc, ftw_libuv_callback_read_pipe);
    if (rc) {
        uv_loop_close(&loop);
        return rc;
    }

    rc = uv_read_start((uv_stream_t*) &stderr_pipe, ftw_libuv_callback_alloc, ftw_libuv_callback_read_pipe);
    if (rc) {
        uv_loop_close(&loop);
        return rc;
    }

    rc = uv_run(&loop, UV_RUN_DEFAULT);
    if (rc) {
        uv_loop_close(&loop);
        return rc;
    }

    rc = uv_loop_close(&loop);

    return rc;
}

MgErr ftw_libuv_lib_path(LStrHandle path)
{
    MgErr lv_err;
    size_t sz;
    char buffer[32768];
    int rc;

    sz = 32768;
    rc = uv_exepath(buffer, &sz);
    if (rc) {
        return bogusError;
    }

    lv_err = ftw_support_buffer_to_LStrHandle(&path, buffer, sz);

    return lv_err;

}

void ftw_high_resolution_time(uint64_t *nanoseconds)
{
    *nanoseconds = uv_hrtime();
}

MgErr ftw_libuv_reserve(struct ftw_libuv_callsite **inst)
{
    static int callsite = 0;

    /*  Preconditions expected of LabVIEW. */
    ftw_assert(inst);

    /*  Creates a list of socket instances for each CLFN callsite. */
    if (*inst == NULL) {
        callsite++;
        ftw_debug("Reserving: %d", callsite);
        *inst = malloc(sizeof(struct ftw_libuv_callsite));
        ftw_assert(*inst);
        (*inst)->id = callsite;
    }
    else {
        ftw_assert_unreachable("Reserve happened twice; this is a problem with LabVIEW.");
    }

    return mgNoErr;
}

MgErr ftw_libuv_unreserve(struct ftw_libuv_callsite **inst)
{
    /*  Preconditions expected of LabVIEW. */
    ftw_assert(inst);

    if (*inst) {
        ftw_debug("Unreserving: %d", (*inst)->id);
        free(*inst);
        /*  LabVIEW retains the lifetime of this pointer for each session. For this reason,
            NULL its value so that it does not continue to point to freed memory. */
        *inst = NULL;
    }
    else {
        ftw_debug("No-op socket callsite unloaded.");
    }

    return mgNoErr;
}

MgErr ftw_libuv_abort(struct ftw_libuv_callsite **inst)
{
    /*  Preconditions expected of LabVIEW. */
    ftw_assert(inst && *inst);

    return mgNoErr;
}