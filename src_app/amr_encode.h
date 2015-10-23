#ifndef _amr_encode_h
#define _amr_encode_h


typedef  struct amr_encode_handle
{
	void * handle;
	unsigned char channels;
	unsigned int bitsPerSample;
	unsigned int sample_rate;
	enum amr_mode mode;

}amr_encode_handle_t;


typedef void * (*pfun_arm_encode)(void *data,unsigned int length,void * puser);


enum arm_encode_mode 
{
	AMR_MR475_ENCODE_MODE 	= 0x04,
	AMR_MR515_ENCODE_MODE 	= 0x0C,   
	AMR_MR59_ENCODE_MODE 	= 0x14,    
	AMR_MR67_ENCODE_MODE 	= 0x1c,     
	AMR_MR74_ENCODE_MODE 	= 0x24,  
	AMR_MR795_ENCODE_MODE 	= 0x2c,    
	AMR_MR102_ENCODE_MODE 	= 0x34,    
	AMR_MR122_ENCODE_MODE 	= 0x3c,    
	AMR_MRDTX_ENCODE_MODE,   
	AMR_N_MODES_ENCODE_MODE  

};


int amr_encodelib_open(void);
int amr_encodelib_close(void);
void * amr_new_encode(unsigned char channels,unsigned int bitsPerSample,unsigned int sample_rate,enum amr_mode mode);
int amr_file_pcmtoamr(amr_encode_handle_t * encode_handle,pfun_arm_encode fun,void * user, unsigned char * path );
int amr_buff_pcmtoamr(amr_encode_handle_t * encode_handle,pfun_arm_encode fun,void * user, unsigned char * data,unsigned int length );

#endif /*_amr_encode_h*/