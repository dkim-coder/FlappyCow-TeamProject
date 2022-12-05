#include <jni.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <android/log.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#define BUZZER_DEVICE "/dev/buzzer"
JNIEXPORT jint JNICALL
Java_com_quchen_flappycow_Game_BuzzerWrite(JNIEnv *env, jobject thiz, jint t) {

    int fd;
    unsigned char state = 0;
    unsigned char retval;
    unsigned char data;

    time_t start, end;

    fd = open(BUZZER_DEVICE, O_RDWR);

    /*if(fd < 0) {
        printf("DEVICE open error: %s\n", BUZZER_DEVICE);
        exit(1);
    }*/

    //(void)signal(SIGINT, user_signal1);
    //printf("Press <Ctrl+c> to exit.\n");

    start = time(NULL);
    while((end - start) <= t) {
        if(state!=0) {
            state=0;
            data=1;
            retval=write(fd,&data,1);
            if(retval<0) {
                printf("Write Error!\n");
                return -1;
            }
        } else {
            state =1;
            data=0;
            retval=write(fd,&data,1);
            if(retval<0) {
                printf("Write Error!\n");
                return -1;
            }
        }

        end = time(NULL);
        usleep(100000);
    }
    data = 0;
    write(fd,&data,1);

    //printf("Current Buzzer value: %d\n",data);
    close(fd);

    return(0);
}

