#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <jni.h>

#define PROGRAM_USAGE_STRING "usage : %s [0-9]\n"

#define DOTM_MAGIC      0xBC
#define DOTM_SET_ALL    _IOW(DOTM_MAGIC, 0, int)
#define DOTM_SET_CLEAR    _IOW(DOTM_MAGIC, 1, int)


JNIEXPORT jint JNICALL
Java_com_quchen_flappycow_Game_Dotmatrix(JNIEnv *env, jclass clazz, jint data) {

        int fd, num , i;

      /*  if(argc <=1){
            fprintf(stderr, PROGRAM_USAGE_STRING, argv[0]);
            return -1;
        }*/
        num = data;
        /*if (num < 0 || num >9) {
            fprintf(stderr, PROGRAM_USAGE_STRING, argv[0]);
            return -1;
        }*/

        fd = open("/dev/dotmatrix", O_WRONLY);
        if(fd != -1){


            write(fd, &num, sizeof (num));
                usleep(50000);



            close(fd);
        } /*else {
            fprintf (stderr, "error opening device\n");
            return -1;
        }*/
        return 0;



}