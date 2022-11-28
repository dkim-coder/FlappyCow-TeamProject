#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

#define LCD_MAGIC	0xBD            // magic number setting 필요
#define LCD_SET_CURSOR_POS	_IOW(LCD_MAGIC, 0 ,int)

/* 게임 시작과 종료를 lcd device에 표현하기 위한 함수 구현 */
/* 매개변수로 true가 들어오면 게임 시작 메시지 출력
   매개변수로 false가 들어오면 게임 종료 메시지를 출력 */

JNIEXPORT jint JNICALL
Java_com_quchen_flappycow_Game_LcdWrite1(JNIEnv *env, jobject thiz, jstring s) {
    int fd, pos, i;

    // java 문자열로부터 c 문자열로 바꾸기
    const char *s_c = (*env)->GetStringUTFChars(env,s,0);

    fd = open("/dev/lcd", O_WRONLY);
    if (fd < 0) {
        //__android_log_print(ANDROID_LOG_ERROR, "LcdWrite","Lcd device file open error");
        return -1;
    }

    pos = 0;
    ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
    write(fd, NULL, 32);      // 디바이스 장치 기존에 쓰여 있는 값 초기화 하는 부분
    ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
    write(fd, s_c, strlen(s_c));

    close(fd);

    // 문자열 자원 해지
    (*env)->ReleaseStringUTFChars(env,s,s_c);

    return 0;
}


JNIEXPORT jint JNICALL
Java_com_quchen_flappycow_GameView_LcdWrite2(JNIEnv *env, jobject thiz, jint score) {
    int fd, pos, i;

    char s2[16] = "score : ";
    char tmp[3];

    fd = open("/dev/lcd", O_WRONLY);
    if (fd < 0) {
        //__android_log_print(ANDROID_LOG_ERROR, "LcdWrite","Lcd device file open error");
        return -1;
    }


    pos = 16;
    ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
    sprintf(tmp,"%d",score);
    strcat(s2,tmp);
    write(fd, s2,strlen(s2));

    close(fd);

    return 0;
}
