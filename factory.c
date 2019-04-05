#include "include/factory.h"
void* downLoadFile(void *p)
{
	//判断队列是否为空，为空就睡觉，不为空就干活
	pFactory_t pf=(pFactory_t)p;
	pQue_t pq=&pf->que;
	pNode_t pcur;
	int getSuccess;
	while(1)
	{
		pthread_mutex_lock(&pq->mutex);
		if(!pq->queSize)
		{
			pthread_cond_wait(&pf->cond,&pq->mutex);
		}
		getSuccess=queGet(pq,&pcur);
        //puts("test1\n");
        pthread_mutex_unlock(&pq->mutex);
		if(!getSuccess)
		{
            //fflush(stdout);
           // printf("success:%s",pcur->dir);
        //puts("test1\n");
            switch(pcur->codeNum){
            case 0:
                userCreat(&pcur);
                //fflush(stdout);//case后不允许直接跟变量定义加的无用语句 
                ////生成salt并返回客户端 
                //char str[SALT_STR_LEN+1];
                //GenerateStr(str);
                //train t;
                //t.dataLen=strlen(str);
                //strcpy(t.buf,str);
                //sendCycle((*pcur).new_fd,(char*)&t,4+t.dataLen);
                //puts(str); 
                ////接收密文密码 
                //recvCycle((*pcur).new_fd,(char*)&t.dataLen,sizeof(int));
                //printf("%d\n",t.dataLen); 
                //memset(t.buf,0,sizeof(t.buf)); 
                //recvCycle((*pcur).new_fd,(char*)t.buf,t.dataLen);
                //char pass[128]={0};
                //strcpy(pass,t.buf);
                ////printf("%s\n",t.buf); 
                //puts(pass); 
                ////接收邮箱
                //recvCycle((*pcur).new_fd,(char*)&t.dataLen,sizeof(int));
                //memset(t.buf,0,sizeof(t.buf));
                //recvCycle((*pcur).new_fd,(char*)t.buf,t.dataLen);
                //char email[255]={0};
                //strcpy(email,t.buf);
                //puts(email);
                ////接收昵称
                //recvCycle((*pcur).new_fd,(char*)&t.dataLen,sizeof(int));
                //memset(t.buf,0,sizeof(t.buf));
                //recvCycle((*pcur).new_fd,(char*)t.buf,t.dataLen);
                //char nickname[255]={0};
                //strcpy(nickname,t.buf);
                ////创建用户并返回状态
                //int stat=userReg((*pcur).dir,str,(unsigned char*)pass,email,nickname);
                //memset(t.buf,0,sizeof(t.buf));
                ////itoa(stat,t.buf,10);
                //sprintf(t.buf,"%d",stat);
                //t.dataLen=sizeof(t.buf);
                //sendCycle((*pcur).new_fd,(char*)&t,4+t.dataLen);
                break;
            case 1:
                userLogin(&pcur);
            }
			free(pcur);
		}
	}
}

void factoryInit(pFactory_t pf,int threadNum,int capacity)
{
	memset(pf,0,sizeof(Factory_t));
	pf->pthid=(pthread_t*)calloc(threadNum,sizeof(pthread_t));
	pf->threadNum=threadNum;
	pthread_cond_init(&pf->cond,NULL);
	queInit(&pf->que,capacity);
}

void factoryStart(pFactory_t pf)
{
	int i;
	if(0==pf->startFlag)
	{
		for(i=0;i<pf->threadNum;i++)
		{
			pthread_create(pf->pthid+i,NULL,downLoadFile,pf);
		}
		pf->startFlag=1;
	}
}

