###FUNCTION
流媒体音频系统，支持pcm、amr、mp3文件和流媒体编解码，可裁剪，高实时性，低cpu占用。支持8k、16k采样，与这两种模式相关接口是：ADC_SAMPLE_RATE、adc_new_user()

###USE
main.c中包含了采样pcm -> 编码amr ->解码amr -> 获取pcm -> 播放这个完整的循环过程示范，这仅仅是这一流程的示范


###LICENCE

MIT

###OTHERS
jweihsz@qq.com