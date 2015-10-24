#include<stdio.h>
#include<fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include "common.h"
#include "amr_loadlib.h"
#include "amr_encode.h"
#include "amr_decode.h"
#include "pcm_dev.h"
#include "mp3_decode.h"
#include "queue.h"





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



	pout_file = fopen("/tmp/hello_new_test_pcm","w+");
	if(NULL == pout_file)
	{
		dbg_printf("open fail ! \n");
		return (-1);

	}
#if 1
	amr_file_amrtopcm(new_handle,amrtopcm,pout_file,"/var/huiwei/test.amr");
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

	
	pout_file = fopen("/tmp/88888888_amr.amr","w+");
	if(NULL == pout_file)
	{
		dbg_printf("open fail ! \n");
		return (-1);

	}
	fwrite("#!AMR\n",1,6,pout_file);



#if 1
	amr_file_pcmtoamr(new_handle,pcmtoamr,NULL,"/tmp/9999999.pcm");
#else
//	FILE * open_file = fopen("./hellotest_pcm_back","r");
	FILE * open_file = fopen("/tmp/9999999.pcm","r");


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



#if 0



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


#if 1
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
	adc_dev_test_pcm = fopen("./9999999.pcm","w+");  /*这里是8000采样，但在pc上播放的时候要用11025hz进行播放测试*/
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

#endif
	return(0);
}



#endif



#if 1

#define  compare_and_swap(lock,old,set)		__sync_bool_compare_and_swap(lock,old,set)
#define  fetch_and_add(value,add)			__sync_fetch_and_add(value,add)
#define	 fetch_and_sub(value,sub)			__sync_fetch_and_sub(value,sub)	

#define	 FILE_MAX_NUM			(100)

typedef struct ring_queue
{
	void **data;
	char *flags;
	unsigned int size;
	unsigned int num;
	unsigned int head;
	unsigned int tail;

} ring_queue_t;


typedef  enum 
{
	SPEAKER = 1,
	PCM_FILE,
	PCM_STREAM,
	MP3_FILE,
	AMR_FILE,
	AMR_STREAM,
	UNKNOW_ITEM_TYPE,
	
}item_type;


typedef struct spk_data
{
	unsigned int sample_rate;
	unsigned int data_length;
	unsigned char data[0];
}spk_data_t;

typedef  enum 
{
	PCM_FILE_TYPE =1,
	MP3_FILE_TYPE,
	AMR_FILE_TYPE,
	UNKNOW_FILE_TYPE
	
}file_type_m;



typedef enum
{
	VOLUME_MID = 0x02,
	VOLUME_MAX = 0x03,
	VOLUME_UNKNOW,
}volume_enum_t;

struct file_node
{
    char * file_name;
	file_type_m type;
    TAILQ_ENTRY(file_node) links; 
};

typedef  struct voice_files
{
	volatile unsigned int num;
	pthread_mutex_t     mutex;
	TAILQ_HEAD(,file_node)file_queue;
}voice_files_t;



typedef struct voice_handle
{

	pthread_mutex_t mutex_spk;
	pthread_cond_t cond_spk;
	ring_queue_t spk_msg_queue;
    volatile unsigned int spk_msg_num;

	pthread_mutex_t mutex_file;
	pthread_cond_t cond_file;
    volatile unsigned int file_msg_num;
	voice_files_t * pvoice_file;

	pthread_mutex_t mutex_mic;
	pthread_cond_t cond_mic;
    volatile unsigned int mic_run;
	
	
	void * da_user;
	void * ad_user;
	amr_decode_handle_t * pamr_decode_handle;
	amr_encode_handle_t * pamr_encode_handle;
	mp3_handle_t * pmp3_decode_handle;


	item_type which_item;
	
}voice_handle_t;



static voice_handle_t *  pvoice_center = NULL;


static int ring_queue_init(ring_queue_t *queue, int buffer_size)
{
    queue->size = buffer_size;
    queue->flags = (char *)calloc(1,queue->size);
    if (queue->flags == NULL)
    {
        return -1;
    }
    queue->data = (void **)calloc(queue->size, sizeof(void*));
    if (queue->data == NULL)
    {
        free(queue->flags);
        return -1;
    }
    queue->head = 0;
    queue->tail = 0;
    memset(queue->flags, 0, queue->size);
    memset(queue->data, 0, queue->size * sizeof(void*));
    return 0;
}



static int ring_queue_push(ring_queue_t *queue, void * ele)
{
    if (!(queue->num < queue->size))
    {
        return -1;
    }
    int cur_tail_index = queue->tail;
    char * cur_tail_flag_index = queue->flags + cur_tail_index; 
    while (!compare_and_swap(cur_tail_flag_index, 0, 1))
    {
        cur_tail_index = queue->tail;
        cur_tail_flag_index = queue->flags + cur_tail_index;
    }

    int update_tail_index = (cur_tail_index + 1) % queue->size;
	
    compare_and_swap(&queue->tail, cur_tail_index, update_tail_index);
    *(queue->data + cur_tail_index) = ele;
	
    fetch_and_add(cur_tail_flag_index, 1); 
    fetch_and_add(&queue->num, 1);
    return 0;
}


static int  ring_queue_pop(ring_queue_t *queue, void **ele)
{
    if (!(queue->num > 0))
        return -1;
    int cur_head_index = queue->head;
    char * cur_head_flag_index = queue->flags + cur_head_index;

    while (!compare_and_swap(cur_head_flag_index, 2, 3)) 
    {
        cur_head_index = queue->head;
        cur_head_flag_index = queue->flags + cur_head_index;
    }

    int update_head_index = (cur_head_index + 1) % queue->size;
    compare_and_swap(&queue->head, cur_head_index, update_head_index);
    *ele = *(queue->data + cur_head_index);
	
    fetch_and_sub(cur_head_flag_index, 3);
    fetch_and_sub(&queue->num, 1);
    return 0;
}


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



static void raise_volume(short * src,unsigned int length,volume_enum_t volume)
{
	if(NULL==src && 0== length)
	{
		dbg_printf("please check the param ! \n");
		return;
	}

	if(VOLUME_MID != volume && VOLUME_MAX != volume)
	{
		dbg_printf("not in the limit ! \n");
		return;
	}

	#define	UNSHORT_MAX_VALUE		(65535u)
	int i = 0;
	unsigned short* pvalue = (unsigned short *)(src);
	unsigned int temp_value = 0;
	for(i=0;i<length;++i)
	{
		temp_value = (*pvalue * volume);
		if(temp_value > UNSHORT_MAX_VALUE)
		{
			temp_value = UNSHORT_MAX_VALUE;	
		}
		*pvalue = temp_value;
		pvalue += 1;
	}

}




int voice_push_file(voice_handle_t * factory,const unsigned char * path,file_type_m type)
{

	
	if(NULL == path || NULL == factory || NULL == factory->pvoice_file )
	{
		dbg_printf("the file is not exit ! \n");
		return(-1);
	}

	
	if(factory->pvoice_file->num >= FILE_MAX_NUM)
	{
		dbg_printf("out of the limit ! \n");
		return(-2);
	}
	

	struct file_node * pfile = calloc(1,sizeof(*pfile));
	if(NULL == pfile)
	{
		dbg_printf("the file is not exit ! \n");
		return(-2);
	}
	pfile->type = type;

	asprintf(&pfile->file_name,"%s",path);

	pthread_mutex_lock(&factory->pvoice_file->mutex);
	
	TAILQ_INSERT_TAIL(&factory->pvoice_file->file_queue,pfile,links);
	factory->pvoice_file->num += 1;
	pthread_mutex_unlock(&factory->pvoice_file->mutex);

	volatile unsigned int *task_num = &factory->file_msg_num;
	fetch_and_add(task_num, 1);
	pthread_cond_signal(&(factory->cond_file));
	
	return (0);
}


static void * voice_pop_file(voice_handle_t * factory)
{

	
	if(NULL == factory || NULL == factory->pvoice_file )
	{
		dbg_printf("check the param \n");
		return(NULL);
	}

	struct file_node * pfile = NULL;
	pthread_mutex_lock(&factory->pvoice_file->mutex);
	pfile =  TAILQ_FIRST(&factory->pvoice_file->file_queue);
	if(NULL == pfile)
	{
		pthread_mutex_unlock(&factory->pvoice_file->mutex);
		return(NULL);
	}

	factory->pvoice_file->num -= 1;
	TAILQ_REMOVE(&factory->pvoice_file->file_queue,pfile,links);
	pthread_mutex_unlock(&factory->pvoice_file->mutex);

	volatile unsigned int *handle_num = &(factory->file_msg_num);
	fetch_and_sub(handle_num, 1);  
	return(pfile);

}



static int  voice_push_spk(voice_handle_t * factory,void * data )
{

	int ret = 1;
	int i = 0;
	if(NULL ==factory ||  NULL==data)
	{
		dbg_printf("check the param ! \n");
		return(-1);

	}

	pthread_mutex_lock(&(factory->mutex_spk));

	for (i = 0; i < 1000; i++)
	{
	    ret = ring_queue_push(&factory->spk_msg_queue, data);
	    if (ret < 0)
	    {
	        usleep(i);
	        continue;
	    }
	    else
	    {
	        break;
	    }	
	}
    if (ret < 0)
    {
		pthread_mutex_unlock(&(factory->mutex_spk));
		return (-2);
    }
    else
    {
		volatile unsigned int *task_num = &factory->spk_msg_num;
    	fetch_and_add(task_num, 1);
    }

    pthread_mutex_unlock(&(factory->mutex_spk));
	pthread_cond_signal(&(factory->cond_spk));
	
	return(0);
}


static void * amrtopcm(void * arg,unsigned int length,void * user)
{

	voice_handle_t * factory = (voice_handle_t*)user;
	if(NULL == factory || NULL == arg || 0 == length)
	{
		dbg_printf("please check the param ! \n");
		return(NULL);
	}

	spk_data_t * pcm_data = NULL;
	pcm_data = calloc(1,sizeof(*pcm_data)+length*2);
	if(NULL == pcm_data)
	{
		dbg_printf("calloc fail ! \n");
		return(NULL);
	}

	raise_volume((unsigned short *)arg,(length+1)/2,VOLUME_MAX);
	
	playback_1c_to_2c(pcm_data->data,(unsigned char *)arg,length);
	pcm_data->data_length = length*2;
	pcm_data->sample_rate = 7996; 

	voice_push_spk(factory,pcm_data);
	pcm_data = NULL;
	
	return(NULL);
}


FILE * pfile = NULL;

FILE * pfile_last = NULL;
static void * voice_amrtopcm(void * arg,unsigned int length,void * user)
{

#if 0
	voice_handle_t * factory = (voice_handle_t*)user;
	if(NULL == factory || NULL == arg || 0 == length)
	{
		dbg_printf("please check the param ! \n");
		return(NULL);
	}

	spk_data_t * pcm_data = NULL;
	pcm_data = calloc(1,sizeof(*pcm_data)+length*2);
	if(NULL == pcm_data)
	{
		dbg_printf("calloc fail ! \n");
		return(NULL);
	}

	playback_1c_to_2c(pcm_data->data,(unsigned char *)arg,length);
	pcm_data->data_length = length*2;
	pcm_data->sample_rate = 7000; /*9000的效果优于8000*/

	voice_push_spk(factory,pcm_data);
	pcm_data = NULL;

#endif


	#if 1
	static unsigned int flag = 0;
	if(flag == 0 )
	{
		flag = 1;
		pfile_last = fopen("/tmp/9999999.pcm","w+");
	}
	fwrite(arg,1,length,pfile_last);

	#endif




	return(NULL);
}



static void * voice_pcmtoamr(void * data,unsigned int length,void * user)
{


	voice_handle_t * factory = (voice_handle_t*)user;
	if(NULL == factory || NULL == data || 0 == length)
	{
		dbg_printf("please check the param ! \n");
		return(NULL);
	}

	if(NULL == factory->pamr_decode_handle)
	{
		dbg_printf("check the pamr decode handle ! \n");
		return(NULL);
	}
	
	amr_buff_amrtopcm(factory->pamr_decode_handle,voice_amrtopcm,factory,data,length);	


	return(NULL);
}



static enum mad_flow voice_mp3_input(void *data,struct mad_stream *stream)
{
	mp3_handle_t * handle = (mp3_handle_t *)data;
	if(NULL == handle)
	{
		dbg_printf("please check the param ! \n");
		return(MAD_FLOW_STOP);
	}

    mp3_node_t *mp3fp = &(handle->node);
    int ret_code;
    int unproc_data_size;
    int copy_size;
	
    if(mp3fp->fpos < mp3fp->flen)
    {
        unproc_data_size = stream->bufend - stream->next_frame;
        memcpy(mp3fp->fbuf, mp3fp->fbuf+mp3fp->fbsize-unproc_data_size, unproc_data_size);
        copy_size = MP3_FRAME_SIZE - unproc_data_size;
        if(mp3fp->fpos + copy_size > mp3fp->flen)
        {
            copy_size = mp3fp->flen - mp3fp->fpos;
        }
        fread(mp3fp->fbuf+unproc_data_size, 1, copy_size, mp3fp->fp);
        mp3fp->fbsize = unproc_data_size + copy_size;
        mp3fp->fpos += copy_size;
        mad_stream_buffer(stream, mp3fp->fbuf, mp3fp->fbsize);
        ret_code = MAD_FLOW_CONTINUE;
    }
    else
    {
        ret_code = MAD_FLOW_STOP;
    }
    return ret_code;

}


static enum mad_flow voice_mp3_error(void *data,struct mad_stream *stream,struct mad_frame *frame)
{
	dbg_printf("get a bug ! \n");
    return MAD_FLOW_CONTINUE;
}


static enum mad_flow voice_mp3_output(void *data,struct mad_header const *header,struct mad_pcm *pcm)
{
    unsigned int nchannels, nsamples;
    unsigned int rate;
    mad_fixed_t const *left_ch, *right_ch;
    rate = pcm->samplerate;   /*从这里就可以调整pcm的信息*/
    nchannels = pcm->channels;
    nsamples = pcm->length;
    left_ch = pcm->samples[0];
    right_ch = pcm->samples[1];
	
	unsigned char pcm_buff[1024*8];
	unsigned int  pcm_length = 0;
    while (nsamples--)
    {
        signed int sample;
        sample = scale(*left_ch++);
		char sound0;
		sound0 = (sample >> 0) & 0xff;
		pcm_buff[pcm_length++] = sound0;
		sound0 = (sample >> 8) & 0xff;
	  	pcm_buff[pcm_length++] = sound0;
        if (nchannels == 2)
        {
            sample = scale(*right_ch++);
			sound0 = (sample >> 0) & 0xff;
          	pcm_buff[pcm_length++] = sound0;
			sound0 = (sample >> 8) & 0xff;
         	pcm_buff[pcm_length++] = sound0;
        }
    }
/*contain_of()*/

	spk_data_t * pcm_data = NULL;
	pcm_data = calloc(1,sizeof(*pcm_data)+pcm_length);
	if(NULL == pcm_data)return MAD_FLOW_CONTINUE;
	memmove(pcm_data->data,pcm_buff,pcm_length);
	pcm_data->data_length = pcm_length;
	pcm_data->sample_rate = rate;
	voice_push_spk(pvoice_center,pcm_data);
	pcm_data = NULL;
	
    return MAD_FLOW_CONTINUE;
}



static int voice_play_file(voice_handle_t * factory,struct file_node * node)
{
	if(NULL == node || NULL == factory)
	{
		dbg_printf("check the param ! \n");
		return(-1);
	}

	if(NULL == node->file_name || access(node->file_name,F_OK) != 0)
	{
		dbg_printf("the file is not exit ! \n");
		return(-2);

	}

	if(PCM_FILE_TYPE == node->type)
	{
	
		FILE * file_pcm = NULL;
		unsigned int read_length = 0;
		file_pcm = fopen(node->file_name,"r");
		if(NULL == file_pcm)
		{
			dbg_printf("open fail ! \n");
			return(-3);
		}
		unsigned char buff[1024];
		spk_data_t * pcm_data = NULL;
		while( ! feof(file_pcm))
		{
			read_length = fread(buff,1,1024,file_pcm);
			if(read_length > 0 )
			{
				pcm_data = calloc(1,sizeof(*pcm_data)+read_length*2);
				playback_1c_to_2c(pcm_data->data,buff,read_length);
				pcm_data->data_length = read_length * 2;
				pcm_data->sample_rate = 11025;
				voice_push_spk(factory,pcm_data);
				pcm_data = NULL;
			}
		}
		fclose(file_pcm);
	}
	else if(MP3_FILE_TYPE == node->type)
	{
		if(NULL == factory->pmp3_decode_handle )
		{
			dbg_printf("pmp3_decode_handle is null, please check it ! \n");
			return(-1);
		}
		mp3_play(factory->pmp3_decode_handle,node->file_name);	
	}
	else if(AMR_FILE_TYPE == node->type)
	{

		if(NULL == factory->pamr_decode_handle)
		{
			dbg_printf("please init the decode mode of amr ! \n");
			return(-1);
		}
		amr_file_amrtopcm(factory->pamr_decode_handle,amrtopcm,factory,node->file_name);
	}
	else
	{
		dbg_printf("unknow file type ! \n");

	}


	return(0);
}

static void *  voice_file_fun(void * arg)
{
	voice_handle_t * factory = (voice_handle_t * )arg;
	if(NULL == factory)
	{
		dbg_printf("please check the param ! \n");
		return(NULL);
	}

	voice_files_t * file_queue = (voice_files_t*)(factory->pvoice_file);

	if(NULL == file_queue)
	{
		dbg_printf("please init the file_queue ! \n");
		return(NULL);
	}

	struct file_node * pfile = NULL;
	
	int is_run = 1;
	while(is_run)
	{
        pthread_mutex_lock(&(factory->mutex_file));
        while (0 == factory->file_msg_num)
        {
            pthread_cond_wait(&(factory->cond_file), &(factory->mutex_file));
        }
		pfile = voice_pop_file(factory);
		pthread_mutex_unlock(&(factory->mutex_file));
		if(NULL == pfile)continue;
		
		voice_play_file(factory,pfile);
		
		if(NULL != pfile->file_name)
		{
			free(pfile->file_name);
			pfile->file_name = NULL;
		}
		free(pfile);
		pfile = NULL;

	}

	return(NULL);

}




static int voice_run_mic(voice_handle_t * factory)
{
	if(NULL == factory || NULL == factory->ad_user )
	{
		dbg_printf("check the param ! \n");
		return(-1);
	}
	volatile  unsigned int * flag = &(factory->mic_run);
	compare_and_swap(flag, 0, 1);
	pthread_cond_signal(&(factory->cond_mic));
	return(0);
}



static int voice_stop_mic(voice_handle_t * factory)
{
	if(NULL == factory || NULL == factory->ad_user )
	{
		dbg_printf("check the param ! \n");
		return(-1);
	}
	volatile  unsigned int * flag = &(factory->mic_run);
	compare_and_swap(flag, 1, 0);

	return(0);
}


static void *  voice_mic_fun(void * arg)
{
	voice_handle_t * factory = (voice_handle_t * )arg;
	if(NULL == factory)
	{
		dbg_printf("please check the param ! \n");
		return(NULL);
	}

	adc_user_t * pad_user = (adc_user_t*)(factory->ad_user);
	if(NULL == pad_user)
	{
		dbg_printf("please init the ad modual ! \n");
		return(NULL);
	}
	
	amr_encode_handle_t * amr_ecode = (amr_encode_handle_t*)(factory->pamr_encode_handle);
	if(NULL == amr_ecode)
	{
		dbg_printf("please init the amr encode modual ! \n");
		return(NULL);
	}


	unsigned int frame_szie = 0;
	unsigned int read_size = 0;
	unsigned char is_16bit = 0;
	frame_szie = amr_ecode->sample_rate / 50;
	read_size = frame_szie * amr_ecode->channels * (amr_ecode->bitsPerSample/8);

	if( pad_user->sample_rate  == amr_ecode->sample_rate*2 )
	{
		read_size *= 2;	
		is_16bit = 1;
	}

	int is_run = 1;
	unsigned char pcm_buff[read_size];
	short raw_buff[read_size/2];
	
	unsigned int i = 0;
	unsigned int count = 0;
	unsigned int  real_read_length = 0;

	spk_data_t * pcm_data = NULL;


	
	while(is_run)
	{
        pthread_mutex_lock(&(factory->mutex_mic));
        while (0 == factory->mic_run)
        {
            pthread_cond_wait(&(factory->cond_mic), &(factory->mutex_mic));
        }
		pthread_mutex_unlock(&(factory->mutex_mic));
		real_read_length = adc_read_data(pad_user,pcm_buff,read_size);
		if(real_read_length > 0 )
		{
	
			if(0x01 == is_16bit)
			{
				for(i=0;i<real_read_length; i+=4)
				{
					raw_buff[count] =  *(short*)(&pcm_buff[i]);
					count += 1;
				}
				amr_buff_pcmtoamr(amr_ecode,voice_pcmtoamr,factory,(unsigned char *)&raw_buff[0],count*2);
				count = 0;

			}
			else
			{
				amr_buff_pcmtoamr(amr_ecode,voice_pcmtoamr,factory,pcm_buff,real_read_length);

			}

		}		
		
		
	}

	return(NULL);

}


static void *  voice_spk_fun(void * arg)
{
	voice_handle_t * factory = (voice_handle_t * )arg;
	if(NULL == factory)
	{
		dbg_printf("please check the param ! \n");
		return(NULL);
	}

	dac_user_t * pda_user = (dac_user_t * )(factory->da_user);
	if(NULL == pda_user)
	{
		dbg_printf("please init the da handle ! \n");
		return(NULL);
	}

	int ret = 0;
	int i = 0;
	int is_run = 1;
	spk_data_t * spkdata = NULL;
	
	speaker_enable(1);
	while(is_run)
	{
        pthread_mutex_lock(&(factory->mutex_spk));
        while (0 == factory->spk_msg_num)
        {
            pthread_cond_wait(&(factory->cond_spk), &(factory->mutex_spk));
        }
		ret = ring_queue_pop(&(factory->spk_msg_queue), (void **)&spkdata);
		pthread_mutex_unlock(&(factory->mutex_spk));
		
		volatile unsigned int *handle_num = &(factory->spk_msg_num);
		fetch_and_sub(handle_num, 1);  

		if(ret != 0 || NULL == spkdata)continue;

		if(pda_user->sample_rate  != spkdata->sample_rate )
		{
			pda_user->sample_rate = spkdata->sample_rate;
			dac_config_review(pda_user);
		}
		
		dac_write_data(pda_user,spkdata->data,spkdata->data_length);
		free(spkdata);
		spkdata = NULL;

	}
	speaker_enable(0);
	return(NULL);

}




static int voice_handle_init(void)
{
	int ret = -1;


	if(NULL != pvoice_center)
	{
		dbg_printf("has been init ! \n");
		return(-2);
	}

	pvoice_center = calloc(1,sizeof(*pvoice_center));
	if(NULL == pvoice_center)
	{
		dbg_printf("calloc fail ! \n");
		return(-2);
	}


	ret = ring_queue_init(&pvoice_center->spk_msg_queue, 1024);
	if(ret < 0 )
	{
		dbg_printf("ring_queue_init  fail \n");
		return(-3);
	}
    pthread_mutex_init(&(pvoice_center->mutex_spk), NULL);
    pthread_cond_init(&(pvoice_center->cond_spk), NULL);
	pvoice_center->spk_msg_num = 0;


	voice_files_t * new_voice_file = calloc(1,sizeof(*new_voice_file));
	if(NULL == new_voice_file)
	{
		dbg_printf("new_voice_file fail ! \n");
		return(-4);
	}
	new_voice_file->num = 0;
	pthread_mutex_init(&(new_voice_file->mutex), NULL);
	TAILQ_INIT(&new_voice_file->file_queue);
	pvoice_center->pvoice_file = new_voice_file;
    pthread_mutex_init(&(pvoice_center->mutex_file), NULL);
    pthread_cond_init(&(pvoice_center->cond_file), NULL);
	pvoice_center->file_msg_num = 0;


    pthread_mutex_init(&(pvoice_center->mutex_mic), NULL);
    pthread_cond_init(&(pvoice_center->cond_mic), NULL);
	pvoice_center->mic_run= 0;
	
	
	
	ret = dac_open_dev();
	if(ret != 0)
	{
		dbg_printf("open the dac dev fail ! \n");
		return(-5);
	}
	pvoice_center->da_user = (dac_user_t*)dac_new_user(2,16,8000);

	ret = adc_open_dev();
	if(ret != 0)
	{
		dbg_printf("adc_open_dev fail ! \n");
		return(-6);
	}
	pvoice_center->ad_user = (adc_user_t*)adc_new_user(1,16,16000);
	if(NULL == pvoice_center->ad_user)
	{
		dbg_printf("adc_new_user fail ! \n");
		return(-7);
	}


	ret = amr_decodelib_open();
	if(ret != 0)
	{
		dbg_printf("amr_decodelib_open  fail ! \n");
		return(-6);
	}
	pvoice_center->pamr_decode_handle = amr_new_decode(1,16,8000,AMR_MR122_HEADER/*AMR_MR515_HEADER*/);
	if(NULL ==  pvoice_center->pamr_decode_handle)
	{
		dbg_printf("amr_new_decode  fail ! \n");
		return(-7);
	}

	ret = amr_encodelib_open();
	if(ret != 0)
	{
		dbg_printf("amr_encodelib_open  fail ! \n");
		return(-8);
	}
	pvoice_center->pamr_encode_handle = amr_new_encode(1,16,8000,AMR_MR515);
	if(NULL == pvoice_center->pamr_encode_handle)
	{
		dbg_printf("pvoice_center->pamr_encode_handle fail ! \n");
		return(-9);
	}

	ret = mp3_open_decodelib( );
	if(0 !=  ret )
	{
		dbg_printf("open the mp3  lib fail ! \n");
		return(-8);
	}
	pvoice_center->pmp3_decode_handle = (mp3_handle_t*)mp3_new_handle();
	if(NULL == pvoice_center->pmp3_decode_handle)
	{
		dbg_printf("mp3_new_handle fail ! \n");
		return(-9);
	}
	pvoice_center->pmp3_decode_handle->input = voice_mp3_input;
	pvoice_center->pmp3_decode_handle->output = voice_mp3_output;
	pvoice_center->pmp3_decode_handle->error = voice_mp3_error;

	return(0);
}




int main(void)
{

	int ret = -1;
	ret = voice_handle_init();
	if(ret != 0 )
	{
		dbg_printf("voice_handle_init  fail ! \n");
		return(-1);
	}
	
	pthread_t spk_pthred;
	pthread_create(&spk_pthred, NULL, voice_spk_fun, pvoice_center);
	pthread_detach(spk_pthred);


	pthread_t file_pthred;
	pthread_create(&file_pthred, NULL, voice_file_fun, pvoice_center);
	pthread_detach(file_pthred);

	pthread_t mic_pthred;
	pthread_create(&mic_pthred, NULL, voice_mic_fun, pvoice_center);
	pthread_detach(mic_pthred);

	sleep(1);
	//voice_run_mic(pvoice_center);

	while(1)
	{	

		//voice_push_file(pvoice_center,"/var/huiwei/chinese_wifi_ok.mp3",MP3_FILE_TYPE);
		//voice_push_file(pvoice_center,"/var/huiwei/20151022120325.amr",AMR_FILE_TYPE);
		voice_push_file(pvoice_center,"/var/huiwei/20151022115959.amr",AMR_FILE_TYPE);
		//voice_push_file(pvoice_center,"/var/huiwei/pcm_adc.pcm",PCM_FILE_TYPE);
		
		sleep(10);
		dbg_printf("this is main loop ! \n");


	}

	return(0);
}



#endif
