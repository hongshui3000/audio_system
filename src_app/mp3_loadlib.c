#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <unistd.h>
#include "mp3_loadlib.h"
#include "common.h"
#include "mad.h"



#undef  	DBG_ON
#undef  	FILE_NAME
#define 	DBG_ON  	(0x01)
#define 	FILE_NAME 	"mp3_loadlib:"



typedef void (*mad_decoder_init_pfun)(struct mad_decoder *, void *,
		      enum mad_flow (*)(void *, struct mad_stream *),
		      enum mad_flow (*)(void *, struct mad_header const *),
		      enum mad_flow (*)(void *,struct mad_stream const *,struct mad_frame *),
		      enum mad_flow (*)(void *,struct mad_header const *,struct mad_pcm *),
		      enum mad_flow (*)(void *,struct mad_stream *,struct mad_frame *),
		      enum mad_flow (*)(void *, void *, unsigned int *));
typedef int (*mad_decoder_finish_pfun)(struct mad_decoder *);
typedef int (*mad_decoder_run_pfun)(struct mad_decoder *, enum mad_decoder_mode);
typedef void (*mad_stream_buffer_pfun)(struct mad_stream *,unsigned char const *, unsigned long);
		       


static  mad_decoder_init_pfun  mad_decoder_init_mp3 = NULL;
static  mad_decoder_finish_pfun	 mad_decoder_finish_mp3 = NULL;
static  mad_decoder_run_pfun  mad_decoder_run_mp3 = NULL;
static  mad_stream_buffer_pfun mad_stream_buffer_mp3 = NULL;


#define	 MP3_DECODE_LIB		"/var/huiwei/libmad.so"

static  void *pmp3_decodelib = NULL;


int load_mp3lib_init(void)
{
	if(NULL != pmp3_decodelib)
	{
		dbg_printf("lib has been init ! \n");
		return(-1);
	}
	if(access(MP3_DECODE_LIB,F_OK) != 0 )
	{
		dbg_printf("the lib is not exit ! \n");
		return(-2);
	}

	
	pmp3_decodelib = dlopen(MP3_DECODE_LIB, RTLD_NOW | RTLD_GLOBAL);
	if(NULL == pmp3_decodelib)
	{
		dbg_printf("open the lib fail ! \n");
		return(-3);
	}

	
	mad_decoder_init_mp3= dlsym(pmp3_decodelib,"mad_decoder_init");
	if(NULL == mad_decoder_init_mp3)
	{
		dbg_printf("mad_decoder_init_mp3 fail ! \n");
	}


	mad_decoder_finish_mp3= dlsym(pmp3_decodelib,"mad_decoder_finish");
	if(NULL == mad_decoder_finish_mp3)
	{
		dbg_printf("mad_decoder_finish fail ! \n");
	}


	mad_decoder_run_mp3= dlsym(pmp3_decodelib,"mad_decoder_run");
	if(NULL == mad_decoder_run_mp3)
	{
		dbg_printf("mad_decoder_run_mp3 fail ! \n");
	}

	mad_stream_buffer_mp3= dlsym(pmp3_decodelib,"mad_stream_buffer");
	if(NULL == mad_stream_buffer_mp3)
	{
		dbg_printf("mad_stream_buffer fail ! \n");
	}


	return(0);
}



void mad_decoder_init(struct mad_decoder *decoder, void * puser,
		      enum mad_flow (*input)(void *, struct mad_stream *),
		      enum mad_flow (*header)(void *, struct mad_header const *),
		      enum mad_flow (*filter)(void *,struct mad_stream const *,struct mad_frame *),
		      enum mad_flow (*output)(void *,struct mad_header const *,struct mad_pcm *),
		      enum mad_flow (*error)(void *,struct mad_stream *,struct mad_frame *),
		      enum mad_flow (*message)(void *, void *, unsigned int *))
{
	if(NULL == mad_decoder_init_mp3)
	{
		dbg_printf("mad_decoder_init_mp3  fail ! \n");
		return;
	}
	mad_decoder_init_mp3(decoder,puser,input,header,filter,output,error,message);
	
}


int mad_decoder_finish(struct mad_decoder * decoder)
{
	if(NULL == mad_decoder_finish_mp3)
	{
		dbg_printf("mad_decoder_finish_mp3 is null ! \n");
		return(-1);
	}
	return(mad_decoder_finish_mp3(decoder));

}



int mad_decoder_run(struct mad_decoder * decoder, enum mad_decoder_mode mode)
{
	if(NULL == mad_decoder_run_mp3)
	{
		dbg_printf("mad_decoder_run_mp3 is fail ! \n");
		return(-1);
	}

	return(mad_decoder_run_mp3(decoder,mode));
}


void mad_stream_buffer(struct mad_stream * stream, unsigned char const * buffer, unsigned long length)
{
	if(NULL == mad_stream_buffer_mp3)
	{
		dbg_printf("this is null ! \n");
		return;
	}
	mad_stream_buffer_mp3(stream,buffer,length);

}
		      