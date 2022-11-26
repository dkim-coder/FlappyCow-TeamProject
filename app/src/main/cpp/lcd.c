#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <jni.h>
#include <android/log.h>
#include <stdbool.h>

#define LCD_MAGIC	0xBD            // magic number setting 필요
#define LCD_SET_CURSOR_POS	_IOW(LCD_MAGIC, 0 ,int)

/* 게임 시작과 종료를 lcd device에 표현하기 위한 함수 구현 */
/* 매개변수로 true가 들어오면 게임 시작 메시지 출력
   매개변수로 false가 들어오면 게임 종료 메시지를 출력 */

JNIEXPORT jint JNICALL
Java_com_example_a7segmentcontrol_MainActivity_LcdWrite(JNIEnv *env, jobject thiz, jboolean check)
{
    int fd, pos;
    char game_start[2][16] = {"game start","enjoy your game"};
    char game_end[2][16] = {"game end","press restart"};

    fd = open("/dev/lcd", O_WRONLY);
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "LcdWrite","Lcd device file open error");
        return -1;
    }

    switch(check) {
        case true:
            pos = 0;
            ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
            write(fd, game_start[0], strlen(game_start[0]));

            pos = 16;
            ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
            write(fd, game_start[1], strlen(game_start[1]));
            break;
        case false:
            pos = 0;
            ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
            write(fd, game_end[0], strlen(game_end[0]));

            pos = 16;
            ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
            write(fd, game_end[1], strlen(game_end[0]));
            break;
    }

    close(fd);

    return 0;
}
