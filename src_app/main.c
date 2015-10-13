#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include "common.h"
#include "amr_loadlib.h"
#include "amr_encode.h"
#include "amr_decode.h"




#undef  	DBG_ON
#undef  	FILE_NAME
#define 	DBG_ON  	(0x01)
#define 	FILE_NAME 	"main:"



#if 0

FILE * pout_file = NULL;
void * amrtopcm(void * arg,void * user)
{
	if(NULL == arg )
	{
		dbg_printf("this is null ! \n");
		return(NULL);
	}
	fwrite(arg, (size_t)1, 160*2, pout_file);

	return(NULL);
}


int main(void)
{
	int ret = -1;
	unsigned int read_length = 0;
	dbg_printf("this is a  test ! \n");

	
	ret = amr_decode_init();
	if(ret != 0)
	{
		dbg_printf("amr_decode_init  fail ! \n");
		return(-1);
	}



	pout_file = fopen("./hellotest_pcm","w+");
	if(NULL == pout_file)
	{
		dbg_printf("open fail ! \n");
		return (-1);

	}
#if 0
	amr_file_amrtopcm(amrtopcm,pout_file,"./test.amr");
#else

	unsigned char amr_buff[1024*2];
	FILE * arm_file = fopen("./test.amr","r");
	if(NULL == arm_file)
	{
		dbg_printf("open the file fail ! \n");
		return(-2);
	}

	read_length = fread(amr_buff,1,1024*2,arm_file);
	fclose(arm_file);
	arm_file = NULL;
	amr_buff_amrtopcm(amrtopcm,NULL,0x0C,amr_buff,read_length);

#endif
	
	
	

	dbg_printf("test is over ! \n");
	
	return(0);
}


#endif


#if 1




FILE *pout_file = NULL;




void * pcmtoamr(void * data,unsigned int length,void * user)
{


	fwrite(data, 1, length, pout_file);
	return(NULL);
}



int main(void)
{
	int ret = -1;
	ret = amr_encodelib_open();
	if(ret != 0)
	{
		dbg_printf("open encode lib fail ! \n");
		return(-1);
	}
	amr_encode_handle_t * new_handle = amr_new_encode(1,16,8000,AMR_MR515);
	if(NULL == new_handle)
	{
		dbg_printf("amr_new_encode is fail ! \n");
		return(-2);
	}

	
	pout_file = fopen("./hellotest_amr.amr","w+");
	if(NULL == pout_file)
	{
		dbg_printf("open fail ! \n");
		return (-1);

	}
	fwrite("#!AMR\n",1,6,pout_file);



#if 0
	amr_file_pcmtoamr(new_handle,pcmtoamr,NULL,"./hellotest_pcm_back");
#else
	FILE * open_file = fopen("./hellotest_pcm_back","r");
	if(NULL == open_file)
	{
		dbg_printf("open the file fail ! \n");
		return(-1);
	}
	unsigned int frame_szie = new_handle->sample_rate / 50;
	unsigned int read_size =  frame_szie * new_handle->channels * (new_handle->bitsPerSample/8);
	unsigned int real_read = 0;
	unsigned char read_buff[read_size];
	while(! feof(open_file) )
	{
		real_read = fread(read_buff,1,read_size,open_file);	
		amr_buff_pcmtoamr(new_handle,pcmtoamr,NULL,read_buff,real_read);
	}

#endif
	
	return 0;
}
	


#endif