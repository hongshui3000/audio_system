#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include <pthread.h>
#include "common.h"
#include "amr_loadlib.h"
#include "amr_encode.h"
#include "amr_decode.h"
#include "pcm_dev.h"





#undef  	DBG_ON
#undef  	FILE_NAME
#define 	DBG_ON  	(0x01)
#define 	FILE_NAME 	"main:"



#if 0

FILE * pout_file = NULL;
void * amrtopcm(void * arg,unsigned int length,void * user)
{
	if(NULL == arg )
	{
		dbg_printf("this is null ! \n");
		return(NULL);
	}
	fwrite(arg, 1, length, pout_file);

	return(NULL);
}


int main(void)
{
	int ret = -1;
	unsigned int read_length = 0;
	dbg_printf("this is a  test ! \n");

	
	ret = amr_decodelib_open();
	if(ret != 0)
	{
		dbg_printf("amr_decodelib_open  fail ! \n");
		return(-1);
	}

	amr_decode_handle_t * new_handle = amr_new_decode(1,16,8000,AMR_MR515_HEADER);
	if(NULL ==  new_handle)
	{
		dbg_printf("amr_new_decode  fail ! \n");
		return(-2);

	}



	pout_file = fopen("./hello_new_test_pcm","w+");
	if(NULL == pout_file)
	{
		dbg_printf("open fail ! \n");
		return (-1);

	}
#if 1
	amr_file_amrtopcm(new_handle,amrtopcm,pout_file,"./test.amr");
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
	amr_buff_amrtopcm(new_handle,amrtopcm,NULL,amr_buff,read_length);

#endif
	
	
	

	dbg_printf("test is over ! \n");
	
	return(0);
}


#endif


#if 0




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



#if 1
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



#if 1



static void playback_1c_to_2c(unsigned char dest[], unsigned char src[],int size)
										
{
	int j;

	for (j = 0; j < size / 2; j++) {
		dest[j * 4] = *(src + j * 2);
		dest[j * 4 + 1] = *(src + j * 2 + 1);
		dest[j * 4 + 2] = *(src + j * 2);
		dest[j * 4 + 3] = *(src + j * 2 + 1);
	}
}



int main(void)
{


#if 0
	int ret = -1;
	ret = adc_open_dev();
	if(ret != 0)
	{
		dbg_printf("adc_open_dev fail ! \n");
		return(-1);
	}


	unsigned int read_length = 0;
	unsigned int length_temp = 0;
	FILE * adc_dev_test_pcm = NULL;
	adc_dev_test_pcm = fopen("./pcm_adc.pcm","w+");  /*这里是8000采样，但在pc上播放的时候要用11025hz进行播放测试*/
	if(NULL == adc_dev_test_pcm)
	{
		dbg_printf("open fail ! \n");
		return(-2);
	}
	adc_user_t * user = (adc_user_t*)adc_new_user(1,16,8000);
	
	unsigned char buff[320];
	while(read_length < 1024*100 )
	{
		length_temp = adc_read_data(user,buff,320);
		dbg_printf("the read length is %d  \n",length_temp);
		read_length += length_temp;
		fwrite(buff,1,length_temp,adc_dev_test_pcm);

	}
	fclose(adc_dev_test_pcm);

#else


	int ret = -1;
	ret = dac_open_dev();
	dac_user_t * user = (dac_user_t*)dac_new_user(2,16,11025/*8000*/);
	unsigned int read_length = 0;
	unsigned int length_temp = 0;
	FILE * dac_dev_test_pcm = NULL;
	dac_dev_test_pcm = fopen("./pcm_adc.pcm","r");
	if(NULL == dac_dev_test_pcm)
	{
		dbg_printf("open fail ! \n");
		return(-2);
	}

	unsigned char buff[1024];
	unsigned char raw_buff[1024*2];
	speaker_enable(1);
	while( ! feof(dac_dev_test_pcm))
	{
		length_temp = fread(buff,1,1024,dac_dev_test_pcm);
		playback_1c_to_2c(raw_buff,buff,length_temp);
		dac_write_data(user,raw_buff,length_temp*2);
	}
	speaker_enable(0);

	dbg_printf("open succed ! \n");

	
	return(0);
}



#endif
