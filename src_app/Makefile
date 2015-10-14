

CC = arm-none-linux-gnueabi-gcc


#CC = gcc



LOCAL_INC =  -I./
LOCAL_LIB =  -ldl  -lpthread
LOCAL_SRC =  .




LOCAL_DEV_SRC := \
    	$(LOCAL_SRC)/amr_loadlib.c \
    	$(LOCAL_SRC)/amr_decode.c	\
    	$(LOCAL_SRC)/amr_encode.c	\
    	$(LOCAL_SRC)/pcm_dev.c		\
        $(LOCAL_SRC)/main.c 


 






all:

	${CC}  ${LOCAL_INC}  ${LOCAL_DEV_SRC}   -o   amr_test   ${LOCAL_LIB}

clean:
	rm -rf  amr_test

