#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <unistd.h>
#include "amr_loadlib.h"
#include "amr_encode.h"
#include "common.h"


#undef  	DBG_ON
#undef  	FILE_NAME
#define 	DBG_ON  	(0x01)
#define 	FILE_NAME 	"amr_encode:"

static volatile int amr_encode_lib = 0;





int amr_encodelib_open(void)
{
	int ret = -1;
	if(0  != amr_encode_lib)
	{
		dbg_printf("the lib has been init ! \n");
		return(-1);
	}

	ret = loadlib_amrenc_init();
	if(0 == ret)
	{
		amr_encode_lib = 1;	
	}
	return(ret);
}


int amr_encodelib_close(void)
{
	loadlib_amrenc_deinit();
	amr_encode_lib = 0;

	return(0);
}

void * amr_new_encode(unsigned char channels,unsigned int bitsPerSample,unsigned int sample_rate,enum amr_mode mode)
{

	if(0 == amr_encode_lib)
	{
		dbg_printf("please init the amr_encode_lib ! \n");
		return(NULL);
	}
	amr_encode_handle_t * new_handle = calloc(1,sizeof(amr_encode_handle_t));
	if(NULL == new_handle)
	{
		dbg_printf("calloc is fail ! \n");
		return(NULL);
	}

	new_handle->channels = channels;
	new_handle->bitsPerSample = bitsPerSample;
	new_handle->sample_rate = sample_rate;
	new_handle->mode = mode;
	
	new_handle->handle = Encoder_Interface_init(0);
	if(NULL == new_handle->handle)
	{
		dbg_printf("Encoder_Interface_init fail ! \n");
		return(NULL);
	}

	return(new_handle);
	
}


void amr_free_enhandle(amr_encode_handle_t * encode_handle)
{
	if(NULL != encode_handle)
	{
		if(NULL != encode_handle->handle)
		{
			Encoder_Interface_exit(encode_handle->handle);
			encode_handle->handle = NULL;
		}
		free(encode_handle);
		encode_handle = NULL;
	}
}




static int amr_check_frame(enum arm_encode_mode mode,unsigned int length)
{

	int result = -1;
	switch(mode)
	{
		case AMR_MR475_ENCODE_MODE: 	result = 13; break;
		case AMR_MR515_ENCODE_MODE: 	result = 14; break;
		case AMR_MR59_ENCODE_MODE: 		result = 16; break;
		case AMR_MR67_ENCODE_MODE: 		result = 18; break;
		case AMR_MR74_ENCODE_MODE: 		result = 20; break;
		case AMR_MR795_ENCODE_MODE: 	result = 21; break;
		case AMR_MR102_ENCODE_MODE: 	result = 27; break;
		case AMR_MR122_ENCODE_MODE: 	result = 32; break;
		default : break;
	}
	if(result < 0)return(-1);
	if(result != length)return(-2);

	return(0);


}


int amr_file_pcmtoamr(amr_encode_handle_t * encode_handle,pfun_arm_encode fun,void * user, unsigned char * path )
{

	int ret = -1;
	if(NULL ==encode_handle || NULL == encode_handle->handle )
	{
		dbg_printf("please check the param ! \n");
		return(-1);
	}

	if(NULL == path)
	{
		dbg_printf("please input the right path ! \n");
		return(-2);
	}

	if(access(path,F_OK) != 0 )
	{
		dbg_printf("the file is not exit ! \n");
		return(-3);
	}

	FILE * pfile = NULL;
	pfile = fopen(path,"r");
	if(NULL == pfile)
	{
		dbg_printf("open the file fail ! \n");
		return(-4);
	}

	unsigned int frame_szie = 0;
	unsigned int read_size = 0;
	unsigned int read_length = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	frame_szie = encode_handle->sample_rate / 50;
	read_size = frame_szie * encode_handle->channels * (encode_handle->bitsPerSample/8);
	short out_buff[frame_szie];
	unsigned char read_buff[read_size];

	unsigned char encode_buff[32]; /*the max fream is 32*/
	unsigned int encode_length = 0;

	dbg_printf("frame_szie==%d  read_size==%d  \n",frame_szie,read_size);

	
	while(!feof(pfile))
	{
		read_length = fread(read_buff,1,read_size,pfile);
		if(0 == read_length || read_length !=  read_size)break;
		if(8 == encode_handle->bitsPerSample && 1 == encode_handle->channels )
		{
			for(i=0;i<frame_szie;++i)
			{
				out_buff[i] =(short)((short)read_buff[i] << 7);
			}
		}
		else if(8 == encode_handle->bitsPerSample && 2 == encode_handle->channels)
		{
           for( i=0, j=0; j<frame_szie; j++,i+=2 )
           {
                out_buff[j] =(short)((short)read_buff[i+0] << 7); /*left-channel*/
				//out_buff[j] =(short)((short)read_buff[i+1] << 7); /*right-channel*/
				//out_buff[j] =(short)((short)(((short)read_buff[i+0] + (short)read_buff[i+1]) / 2) << 7);/*(left+right)/2*/	
           }

		}
		else if(16 == encode_handle->bitsPerSample && 1 == encode_handle->channels)
		{
			for(i=0,j=0;j<frame_szie;j++,i+=2)
			{
				out_buff[j] =*(short*)(&read_buff[i]);
			}

		}
		else if(16 == encode_handle->bitsPerSample && 2 == encode_handle->channels)
		{
			for(i=0,j=0;j<frame_szie;j++,i+=4)
			{
				out_buff[j] =*(short*)(&read_buff[i+0]);
				//out_buff[j] =*(short*)(&read_buff[i+2]);
			}
		}
		else
		{
			dbg_printf("check the bitsPerSample  and channels ! \n");
			break;
		}

		encode_length = Encoder_Interface_Encode(encode_handle->handle,encode_handle->mode,out_buff,encode_buff,0);
		ret = amr_check_frame(encode_buff[0],encode_length);
		if(ret != 0 )continue;
		if(NULL != fun)
		{
			fun(encode_buff,encode_length,user);
		}

	}

	fclose(pfile);
	pfile = NULL;

	return(0);
}



int amr_buff_pcmtoamr(amr_encode_handle_t * encode_handle,pfun_arm_encode fun,void * user, unsigned char * data,unsigned int length )
{

	int ret = -1;
	if(NULL == encode_handle || NULL == encode_handle->handle )
	{
		dbg_printf("please check the param ! \n");
		return(-1);
	}

	if(NULL == data || length == 0)
	{
		dbg_printf("please input the right param ! \n");
		return(-2);
	}


	unsigned int frame_szie = 0;
	unsigned int read_size = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	frame_szie = encode_handle->sample_rate / 50;
	read_size = frame_szie * encode_handle->channels * (encode_handle->bitsPerSample/8);
	if(length  != read_size)
	{
		dbg_printf("please check the input size ! \n");
		return(-3);
	}
	
	short out_buff[frame_szie];

	unsigned char encode_buff[32]; 
	unsigned int encode_length = 0;

	dbg_printf("frame_szie==%d  read_size==%d  \n",frame_szie,read_size);

	if(8 == encode_handle->bitsPerSample && 1 == encode_handle->channels )
	{
		for(i=0;i<frame_szie;++i)
		{
			out_buff[i] =(short)((short)data[i] << 7);
		}
	}
	else if(8 == encode_handle->bitsPerSample && 2 == encode_handle->channels)
	{
       for( i=0, j=0; j<frame_szie; j++,i+=2 )
       {
            out_buff[j] =(short)((short)data[i+0] << 7);
       }
	}
	else if(16 == encode_handle->bitsPerSample && 1 == encode_handle->channels)
	{
		for(i=0,j=0;j<frame_szie;j++,i+=2)
		{
			out_buff[j] =*(short*)(&data[i]);
		}

	}
	else if(16 == encode_handle->bitsPerSample && 2 == encode_handle->channels)
	{
		for(i=0,j=0;j<frame_szie;j++,i+=4)
		{
			out_buff[j] =*(short*)(&data[i+0]);
		}
	}
	else
	{
		dbg_printf("check the bitsPerSample  and channels ! \n");
		return(-4);
	}

	encode_length = Encoder_Interface_Encode(encode_handle->handle,encode_handle->mode,out_buff,encode_buff,0);
	ret = amr_check_frame(encode_buff[0],encode_length);
	if(ret != 0 )
	{
		dbg_printf("a bad frame ! \n");
		return(-5);

	}
	if(NULL != fun)
	{
		fun(encode_buff,encode_length,user);
	}
	return(0);
}




