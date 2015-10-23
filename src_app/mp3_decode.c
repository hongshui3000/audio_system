#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "common.h"
#include "mad.h"
#include "mp3_decode.h"
#include "mp3_loadlib.h"



#undef  	DBG_ON
#undef  	FILE_NAME
#define 	DBG_ON  	(0x01)
#define 	FILE_NAME 	"mp3_decode:"


#undef		MP3_TYPE		
#define		MP3_TYPE	"ID3"


static volatile unsigned int mp3lib_isopen = 0;

int mp3_open_decodelib(void)
{
	int ret = -1;
	if(0 != mp3lib_isopen)
	{
		dbg_printf("the lib has been init ! \n");
		return(-1);
	}
	ret = load_mp3lib_init();
	if(ret == 0)
	{
		mp3lib_isopen = 1;	
	}
	
	return(ret);
}

void * mp3_new_handle(void)
{
	if(0 == mp3lib_isopen)
	{
		dbg_printf("please load the mp3 decode lib first ! \n");
		return(NULL);
	}
	mp3_handle_t * new_one = calloc(1,sizeof(*new_one));
	if(NULL == new_one)
	{
		dbg_printf("calloc  fail ! \n");
		return(NULL);
	}

	new_one->error = NULL;
	new_one->input = NULL;
	new_one->output = NULL;
	new_one->user = NULL;
	return(new_one);

}



void mp3_free_handle(void * hanle)
{
	if(NULL == hanle)return;
	free(hanle);
	hanle = NULL;
}


static int mp3_check_type(const unsigned char * path)
{
	if(NULL == path)
	{
		dbg_printf("check the param ! \n");
		return(-1);
	}
	if(access(path,F_OK) != 0 )
	{
		dbg_printf("the mp3 file is not  exit ! \n");
		return(-2);
	}

	FILE * pmp3_file = NULL;
	char buff[3];
	int length = 0;
	pmp3_file = fopen(path,"r");
	if(NULL == pmp3_file)
	{
		dbg_printf("open the file fail ! \n");
		return(-3);
	}

	length = fread(buff,1,3,pmp3_file);
	if(length <= 0  || strncmp(buff,MP3_TYPE,3) != 0 )
	{
		dbg_printf("not a mp3 file ! \n");
		return(-4);
	}

	fclose(pmp3_file);
	pmp3_file = NULL;
	
	return(0);

}


int mp3_play(mp3_handle_t * handle,const unsigned char * path)
{

	int ret = -1;
	if(NULL == handle || NULL == handle->input  || NULL == handle->output || NULL == handle->error )
	{
		dbg_printf("check the param ! \n");
		return(-1);
	}

	if(NULL == path || access(path,F_OK) != 0)
	{
		dbg_printf("the path is not right ! \n");
		return(-2);
	}

	ret = mp3_check_type(path);
	if(ret != 0)
	{
		dbg_printf("this is not a mp3 file ! \n");
		return(-2);
	}
	
    mp3_node_t *mp3fp = &(handle->node);
	mp3fp->fp = fopen(path,"r");
	if(NULL == mp3fp->fp)
	{
		dbg_printf("open the file fail ! \n");
		return(-3);
	}

   	unsigned int flen, fsta, fend;

	fseek(mp3fp->fp, 0, SEEK_SET);
    fsta = ftell(mp3fp->fp);
    fseek(mp3fp->fp, 0, SEEK_END);
    fend = ftell(mp3fp->fp);
    flen = fend - fsta;
    fseek(mp3fp->fp, 0, SEEK_SET);

    mp3fp->fbsize = MP3_FRAME_SIZE;
    mp3fp->fpos = MP3_HEADER_LENGTH;
    mp3fp->flen = flen-MP3_TAIL_LENGTH;

    struct mad_decoder decoder;
    mad_decoder_init(&decoder, handle,handle->input,NULL, NULL, handle->output,handle->error, NULL);
    mad_decoder_run(&decoder, MAD_DECODER_MODE_SYNC);
    mad_decoder_finish(&decoder);

    fclose(mp3fp->fp);
	mp3fp->fp = NULL;

    return 0;
}


