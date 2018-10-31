#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "common.h"

int UsFgetsNum()
{
    int ret;
    char c_buf[BUF_SIZE] = {0};

    fgets(c_buf, BUF_SIZE, stdin);
    setbuf(stdin, NULL);

    for (int i = 0; i < BUF_SIZE; ++i) {
        if (c_buf[i] == '\r' ||
            c_buf[i] == '\n' ||
            c_buf[i] == ' '  ||
            c_buf[i] == '\t' ||
            c_buf[i] == '\v' ||
            c_buf[i] == '\f') {

            c_buf[i] = '\0';
            break;
        }
    }

    ret = (int)strtol(c_buf, '\0', 10);

    return ret;
}

char UsFgetsChar()
{
    char ret;
    char c_buf[BUF_SIZE] = {0};

    fgets(c_buf, BUF_SIZE, stdin);
    setbuf(stdin, NULL);

    if(strlen(c_buf) > 2){
        ret = 'q';
    }
    else{
        ret = c_buf[0];
    }

    return ret;
}
