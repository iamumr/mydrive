#include "include/factory.h"

int main()
{
    Factory_t f;
    factoryInit(&f,THREAD_NUM,QUE_NUM);
    factoryStart(&f);
    int socketFd;
    tcpInit(&socketFd,LISTEN_IP,LISTEN_PORT);
    int new_fd;
    pQue_t pq=&f.que;
    while(1)
    {
        new_fd=accept(socketFd,NULL,NULL);
        char order[2000];
        int dataLen;
        recvCycle(new_fd,(char*)&dataLen,sizeof(int));
        recvCycle(new_fd,order,dataLen); 
        pNode_t pnew=(pNode_t)calloc(1,sizeof(Node_t));
        pnew->new_fd=new_fd;
        pnew->codeNum=atoi(order);
        //printf("%d\n",pnew->codeNum);
        memset(&order,0,sizeof(order));
        recvCycle(new_fd,(char*)&dataLen,sizeof(int));
        recvCycle(new_fd,order,dataLen);
        strcpy(pnew->dir,order);
        puts(order);
        pthread_mutex_lock(&pq->mutex);
        queInsert(pq,pnew);
        pthread_mutex_unlock(&pq->mutex);
        pthread_cond_signal(&f.cond);
    }
}
