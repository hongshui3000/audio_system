#ifndef _mp3_decode_h
#define _mp3_decode_h

#include "mad.h"

typedef enum mad_flow (*error_pfun)(void *data,struct mad_stream *stream,struct mad_frame *frame);
typedef enum mad_flow (*output_pfun)(void *data,struct mad_header const *header,struct mad_pcm *pcm);
typedef enum mad_flow (*input_pfun)(void *data,struct mad_stream *stream);

#undef		MP3_FRAME_SIZE
#define 	MP3_FRAME_SIZE			(4608u)

#define		MP3_HEADER_LENGTH		(10u)
#define		MP3_TAIL_LENGTH			(128u)



typedef struct mp3_node 
{
    FILE *fp;
    unsigned int flen;
    unsigned int fpos; 
    unsigned char fbuf[MP3_FRAME_SIZE]; 
    unsigned int fbsize;
}mp3_node_t;


typedef struct mp3_handle
{
	error_pfun error;
	output_pfun output;
	input_pfun input;
	mp3_node_t node;
	void * user;
}mp3_handle_t;




static inline signed int scale(mad_fixed_t sample)
{

    sample += (1L <= MAD_F_FRACBITS - 16);
    if(sample >= MAD_F_ONE)
        sample = MAD_F_ONE - 1;
    else if(sample < -MAD_F_ONE)
        sample = -MAD_F_ONE;
    return sample >> (MAD_F_FRACBITS + 1 - 16);
}

int mp3_open_decodelib(void);
void * mp3_new_handle(void);
void mp3_free_handle(void * hanle);
int mp3_play(mp3_handle_t * handle,const unsigned char * path);




#endif/*_mp3_decode_h*/
