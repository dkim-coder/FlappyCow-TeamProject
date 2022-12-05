#include <jni.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <android/log.h>

/* 현재까지의 누적 coin을 표시하기 위해서 coin 개수를 매개변수 jint data로 받아서
   디바이스에 쓰기 위한 c/c++ 코드 구현 */

JNIEXPORT jint JNICALL
Java_com_quchen_flappycow_Game_SSegmentWrite(JNIEnv *env, jobject thiz, jint data) {
    int fd, ret;
    unsigned char bytevalues[4];

    if((data < 0) || (data > 9999)) {
        printf("Invalid 7segment data range!\n");
        return -1;
    }
    fd = open("/dev/7segment", O_WRONLY);
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "SSegmentWrite","7segment device file open error");
        return -1;
    }

    bytevalues[0] = data / 1000;
    data = data % 1000;
    bytevalues[1] = data / 100;
    data = data % 100;
    bytevalues[2] = data / 10;
    data = data % 10;
    bytevalues[3] = data;

    ret = write(fd, bytevalues, 4);
    if (ret < 0) {
        __android_log_print(ANDROID_LOG_ERROR,"SSegmentWrite","7Segment write error");
        return -1;
    }

    close(fd);

    return 0;
}

JNIEXPORT jint JNICALL
Java_com_quchen_flappycow_GameOverDialog_SSegmentWrite2(JNIEnv *env, jobject thiz, jint data) {
    int fd, ret;
    unsigned char bytevalues[4];

    if((data < 0) || (data > 9999)) {
        printf("Invalid 7segment data range!\n");
        return -1;
    }
    fd = open("/dev/7segment", O_WRONLY);
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "SSegmentWrite","7segment device file open error");
        return -1;
    }

    bytevalues[0] = data / 1000;
    data = data % 1000;
    bytevalues[1] = data / 100;
    data = data % 100;
    bytevalues[2] = data / 10;
    data = data % 10;
    bytevalues[3] = data;

    ret = write(fd, bytevalues, 4);
    if (ret < 0) {
        __android_log_print(ANDROID_LOG_ERROR,"SSegmentWrite","7Segment write error");
        return -1;
    }

    close(fd);

    return 0;
}