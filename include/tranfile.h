#ifndef __TRANFILE_H__
#define __TRANFILE_H__
#include "func.h"
//小火车
typedef struct{
        int dataLen;
        char buf[1000];
}train;

int sendCycle(int fd,char* p,int sendLen);
int recvCycle(int fd,char* p,int recvLen);
int tranFile(int new_fd);
#endif

