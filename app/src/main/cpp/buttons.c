#include <stdio.h>
#include <string.h> //memory copy
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <jni.h>

#define NUM_BUTTONS 9
// change_cat

JNIEXPORT jint JNICALL
Java_com_quchen_flappycow_GameView_buttons(JNIEnv *env, jclass clazz, jint btn) {
    int btnFd;
    int ret;
    unsigned char *btnValue[NUM_BUTTONS] = { 0, };

    btnFd = open("/dev/buttons", O_RDONLY); // for reading only
    if (btnFd < 0) { fprintf(stderr, "error opening button device\n"); return -1; }


    while(1){
        ret = read(btnFd, btnValue, NUM_BUTTONS);
        if (ret < 0) {
            printf("read error %d\n", ret); return -1; }


        usleep(10);
    }
    close(btnFd);
}