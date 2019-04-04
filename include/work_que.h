#ifndef __WORK_QUE__
#define __WORK_QUE__
#include "func.h"

typedef struct tag_node
{
	int new_fd;
    int token;//用户识别码
    int codeNum;//操作码
    char dir[2000];//操作路径
    struct tag_node *pNext;
}Node_t,*pNode_t;

typedef struct{
	pNode_t queHead,queTail;
	int queCapacity;//队列容量
	int queSize;//队列实时大小
	pthread_mutex_t mutex;
}Que_t,*pQue_t;
void queInit(pQue_t,int);
void queInsert(pQue_t,pNode_t);
int queGet(pQue_t,pNode_t*);
#endif

