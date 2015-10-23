##说明
&#160;&#160;&#160;&#160;这里使用的解码库版本是libmad-0.15.1b，移植的步骤如下：

(1)第一步：
```
./configure CC=arm-none-linux-gnueabi-gcc  --host=arm-linux  --disable-debugging --prefix=../mp3_lib
```

(2)第二步:

```
make
```

(3)第三步:

```
make install
```

###编译注意点：
&#160;&#160;&#160;&#160;执行完第一步后，在makefile 中的129行左右要删除"-fforce-mem"不然编译会不通过。

##库的使用
&#160;&#160;&#160;&#160;如果上面的编译都成功了，那么在个人指定的目录下将能找到libmad.a、mad.h文件，库的使用可以根据该库中自带的示范程序minimad.c来进行使用，但有一点要注意：不要进行预读，不要一个字节一个字节的往da设备中送数据。