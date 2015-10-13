#ifndef _amr_decode_h
#define _amr_decode_h


enum arm_header_mode 
{
	AMR_MR475_HEADER 	= 0x04,
	AMR_MR515_HEADER 	= 0x0C,   
	AMR_MR59_HEADER 	= 0x14,    
	AMR_MR67_HEADER 	= 0x1c,     
	AMR_MR74_HEADER 	= 0x24,  
	AMR_MR795_HEADER 	= 0x2c,    
	AMR_MR102_HEADER 	= 0x34,    
	AMR_MR122_HEADER 	= 0x3c,    
	AMR_MRDTX_HEADER,   
	AMR_N_MODES_HEADER  

};


int amr_decode_init(void);
int amr_file_amrtopcm(void * (*pfun)(void * buff,void * puser),void * user,const unsigned char * path);
int amr_buff_amrtopcm(void * (*pfun)(void * buff,void * puser),void * user,unsigned char header_mode,unsigned char * buff,unsigned int length );


#endif

