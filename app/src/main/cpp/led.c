#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <android/log.h>
#include <jni.h>



JNIEXPORT jint JNICALL
Java_com_quchen_flappycow_Game_LedWrite(JNIEnv *env, jobject thiz, jint data) {
    int fd;
    unsigned char bytedata;
    unsigned char ret;

    /*if(argc !=2) {
        printf("please input the parameter! \n");
        printf("ex)./test_led 7 (0-255)\n");
        return -1;
    }*/

    bytedata =data;
    if ((bytedata < 0) || (bytedata >0xff)){
        printf("Invalid range!\n");
        return -1;
    }

    fd =open("/dev/led",O_RDWR);
    if(fd<0) {
        printf("Device open error : /dev/led\n");
        return -1;
    }

    ret =write(fd, &bytedata, 1);
    if (ret < 0){
        printf("Wirte Error!\n");
        return -1;
    }

    bytedata =0;
    ret =read(fd, &bytedata, 1);
    if(ret < 0) {
        printf("Read Error!\n");
        //__android_log_print(ANDROID_LOG_ERROR, "Read Error!\n");

        return -1;
    }
    printf("Current LED Value : 0x%x\n", bytedata);
    //__android_log_print(ANDROID_LOG_ERROR, "Current LED Value : 0x%x\n", bytedata);

    printf("\n");
    usleep(1000);
    close(fd);

    return 0;
}