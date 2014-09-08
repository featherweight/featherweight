/*
    Copyright (c) 2014 Wirebird Labs LLC. All rights reserved.

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


#include "ftw_nanomsg.h"
#include "../utils/sleep.h"
#include "../utils/alloc.h"
#include "../reqrep.h"

const char *ftw_nanomsg_error (int *error_code)
{
	return "";
}

const char *ftw_nanomsg_version (void)
{
	return "0.4.0-1000";
}

int ftw_nanomsg_send (int s, const void *buf, size_t length, int timeout, int flags)
{
    struct nn_iovec iov;
    struct nn_msghdr hdr;
	
    iov.iov_base = (void*) buf;
    iov.iov_len = NN_MSG;

    hdr.msg_iov = &iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = NULL;
    hdr.msg_controllen = 0;

	nn_setsockopt(s, NN_SOL_SOCKET, NN_SNDTIMEO, &timeout, sizeof(timeout));

    return nn_sendmsg (s, &hdr, flags);
}

int ftw_nanomsg_connect (int s, const char *addr)
{
	int connection_id;
	
	nn_sleep (20);
	connection_id = nn_connect (s, addr);
	
	if ( connection_id >= 0 ) {
		nn_sleep (50);
	}

	return connection_id;
}

int ftw_nanomsg_bind (int s, const char *addr)
{
	int binding_id;
	
	nn_sleep (20);
	binding_id = nn_bind (s, addr);
	
	if ( binding_id >= 0 ) {
		nn_sleep (50);
	}

	return binding_id;
}


int ftw_nanomsg_recv (int s, void *buf, size_t length, int timeout, int flags)
{
	struct nn_iovec iov;
	struct nn_msghdr hdr;

	iov.iov_base = buf;
	iov.iov_len = NN_MSG;

	hdr.msg_iov = &iov;
	hdr.msg_iovlen = 1;
	hdr.msg_control = NULL;
	hdr.msg_controllen = 0;
	
	nn_setsockopt(s, NN_SOL_SOCKET, NN_RCVTIMEO, &timeout, sizeof(timeout));

    return nn_recvmsg (s, &hdr, flags);
}


//static void ftw_nanomsg_router_worker (void* arguments)
//{
//	int incoming_msg_bytes = -1;
//	int router_id = -1;
//	int rc = -1;
//	void *incoming_msg_ptr = NULL;
//	LVUserEventRef *event_publisher;
//	//LStrHandle *response_ptr = DSNewHClr(4);
//	
//	MgErr err; /* Error thrown by the LabVIEW Memory Manager */
//
//	///////////Debug///////////////////////
//	FILE * pFile;
//	pFile = fopen ("c:\\ftw-log.txt","a+");
//	setbuf(pFile, NULL);
//	
//	///////////Debug///////////////////////
//	fprintf (pFile,"Opening log\n");
//
//	event_publisher = ((ftw_nanomsg_router_worker_inputs*)arguments)->ref;
//	router_id = ((ftw_nanomsg_router_worker_inputs*)arguments)->router_id;
//
//	///////////Debug///////////////////////
//	fprintf (pFile,"Event ref: %08x\n", (int)*event_publisher);
//	fprintf (pFile,"RouterID: %08x\n", (int)router_id);
//	
//	while (router_id >= 0)
//	{
//		///////////Debug///////////////////////
//		fprintf (pFile,"Receiving...\n");
//		incoming_msg_bytes = nn_recv(router_id, &incoming_msg_ptr, NN_MSG, 0);
//
//		///////////Debug///////////////////////
//		fprintf (pFile,"Received %d bytes\n", incoming_msg_bytes);
//
//		if (incoming_msg_bytes >=0) {
//
//			UHandle response_handle = NULL;
//			LStrHandle res
//			newStringHandle=(LStrHandle)DSNewHandle(sizeof(int32)+STRING_LENGHT*sizeof(uChar))
//
//			//err = NumericArrayResize(uB, 1, (UHandle*)response_ptr, incoming_msg_bytes);
//			err = NumericArrayResize(uB, 1, (UHandle*)&response_handle, incoming_msg_bytes);
//			//err = DSSetHandleSize (*response_ptr, incoming_msg_bytes+4);
//			
//			fprintf (pFile,"Resize return code: %d\n",err);
//			fprintf (pFile,"New handle size: %d\n", DSGetHandleSize(response_handle));
//
//			if (err == noErr)
//			{
//				MoveBlock(incoming_msg_ptr, LStrBuf(*(LStrHandle)response_handle), incoming_msg_bytes);
//    			LStrLen(*(LStrHandle)response_handle) = IntFrom4Chars(incoming_msg_bytes);
//	//			*( uInt32* )**response_handle = incoming_msg_bytes;
//
//			//	///////////Debug///////////////////////
//				fwrite (*response_handle,1,DSGetHandleSize(response_handle),pFile);
//   // 			
//				rc = PostLVUserEvent(*event_publisher, (void *)response_handle); 
//			}

////			response_to_lv = DSNewHandle (sizeof(int32_t) + incoming_msg_bytes);
//			
//			///////////Debug///////////////////////
//			//fprintf (pFile,"Response handle: %08x\n",(int)response_to_lv);
//			//fprintf (pFile,"Response pointer: %08x\n",(int)*response_to_lv);
//
////			**response_to_lv = incoming_msg_bytes;
//			//*( int32* )*response_to_lv = incoming_msg_bytes;
//		
//			///////////Debug///////////////////////
//			//fprintf (pFile,"Response size1: %02x\n",(int)*( int32* )*response_to_lv);
//			//fprintf (pFile,"response size1: %02x\n",(int)*(*response_ptr+0));
//			//fprintf (pFile,"response size2: %02x\n",(int)*(*response_ptr+1));
//			//fprintf (pFile,"response size3: %02x\n",(int)*(*response_ptr+2));
//			//fprintf (pFile,"response size4: %02x\n",(int)*(*response_ptr+3));
//
//			//memcpy(*response_to_lv+sizeof(int32_t), incoming_msg_data, incoming_msg_bytes);

//			//rc = PostLVUserEvent(*event_publisher, response_to_lv);
//			///////////Debug///////////////////////
//			fprintf (pFile,"PostLVUserEvent: %d\n",rc);
//
//			nn_freemsg (incoming_msg_ptr);
//			if (rc != 0){
//				return;
//			}
//		}
//
//		else {
//			
//			switch (incoming_msg_bytes) {
//
//				case EAGAIN:
//					nn_sleep (10);
//					break;
//
//				default:
//					return;
//			}
//		}
//
//	}
//
//
//	fprintf (pFile,"Closing log\n");
//	fclose (pFile);
//
//
//}

int ftw_nanomsg_router_start (const char *addr)
{
//	struct nn_thread worker_thread;
	int frontend;
//	int backend = NULL;
//	int rc = NULL;
//
//	ftw_nanomsg_router_worker_inputs *args = (ftw_nanomsg_router_worker_inputs (*)) nn_alloc_( sizeof(ftw_nanomsg_router_worker_inputs));
//	args->backend = backend;
//	args->frontend = frontend;
	frontend = nn_socket(AF_SP_RAW, NN_REP);
	ftw_nanomsg_bind(frontend, addr);
//	backend = nn_socket(AF_SP_RAW, NN_REP);
//
//
//	if (frontend >= 0 && backend >= 0) {
//		rc = ftw_nanomsg_bind(router, addr);
//		if (rc > 0) {
////			args->router_id = router;
////			nn_thread_init (&worker_thread, ftw_nanomsg_router_worker, (void *)args);
//			nn_sleep(200);
//			rc = router;
//		}
//	}
//
//	return rc;
	return frontend;
}


int ftw_nanomsg_router_recv (int router_id, void *incoming_msg_body, size_t *incoming_body_size, void *incoming_msg_header, size_t *incoming_header_size, int timeout)
{
	struct nn_iovec iov;
	struct nn_msghdr hdr;
	int rc;

	iov.iov_base = incoming_msg_body;
	iov.iov_len = NN_MSG;

	hdr.msg_iov = &iov;
	hdr.msg_iovlen = 1;
	hdr.msg_control = incoming_msg_header;
	hdr.msg_controllen = NN_MSG;
	
	nn_setsockopt(router_id, NN_SOL_SOCKET, NN_RCVTIMEO, &timeout, sizeof(timeout));

    rc = nn_recvmsg (router_id, &hdr, NN_NOFLAGS);

	if (rc < 0) {
		rc = nn_errno();
		return rc;
	} 
	else {
		*incoming_body_size = rc;
		*incoming_header_size = hdr.msg_controllen;
		
		return 0;
	}
	
}


int ftw_nanomsg_router_stop (int router_id)
{
	//struct nn_thread worker_thread;
	//worker_thread.handle = router_id;
	//nn_thread_term(&worker_thread);
	//return ((ftw_nanomsg_router_worker_outputs (*))(worker_thread.arg))->return_value;

	return ftw_nanomsg_close (router_id);
}

int ftw_nanomsg_close (int s)
{
	nn_sleep(100);
	return nn_close(s);
	nn_sleep(10);
}