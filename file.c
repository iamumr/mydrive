#include "include/factory.h"
#define RECV_BLOCK 65536
int UploadFile(pNode_t* pcur)
{
	train t;
    //接收token
	recvCycle((*pcur)->new_fd,(char*)&t.dataLen,sizeof(int));
	recvCycle((*pcur)->new_fd,(char*)t.buf,t.dataLen);
	char username[255];
	int expir_time;
    //获取有效时间
    int tmp=mysqlToken(t.buf,username,&expir_time);
	if(tmp==0&&(expir_time-time(NULL))>0)
	{
        //有效刷新有效时间
        char query[2000]={0};
        sprintf(query,"UPDATE `user_token` SET expir_time ='%ld' WHERE user_token ='%s'",time(NULL)+863000,t.buf);
        tmp=mysqlQuery(query); 
        ERROR_CHECK(tmp,-1,"TOKEN UPDATE");
        //回复成功信号
        t.dataLen=sizeof(char);
        strcpy(t.buf,"0");
        sendCycle((*pcur)->new_fd,(char*)&t,4+t.dataLen);
		char buf[1000];
		int dataLen;
		//接收文件名
		recvCycle((*pcur)->new_fd,(char*)&dataLen,sizeof(int));
		recvCycle((*pcur)->new_fd,buf,dataLen);
		//接文件大小
		off_t downLoadSize,fileSize,beforeSize,fileSlice;
		recvCycle((*pcur)->new_fd,(char*)&dataLen,sizeof(int));
		recvCycle((*pcur)->new_fd,(char*)&fileSize,dataLen);
		printf("fileSize=%ld\n",fileSize);
		//接文件内容
		int fd;
		fd=open(buf,O_CREAT|O_RDWR,0666);
		ERROR_CHECK(fd,-1,"open");
		fileSlice=fileSize/RECV_BLOCK;
		beforeSize=downLoadSize=0;
		struct timeval start,end;
		gettimeofday(&start,NULL);
		//splice接那么多长度的文件内容
		int fds[2];
		pipe(fds);
		int recvCount;
		if(fileSize>RECV_BLOCK)
		{
			while(downLoadSize+RECV_BLOCK<fileSize)
			{
				recvCount=splice((*pcur)->new_fd,NULL,fds[1],NULL,RECV_BLOCK,SPLICE_F_MORE | SPLICE_F_MOVE);
				ERROR_CHECK(recvCount,-1,"splice1");
				recvCount=splice(fds[0],NULL,fd,NULL,recvCount,SPLICE_F_MORE | SPLICE_F_MOVE);
				ERROR_CHECK(recvCount,-1,"splice2");
				downLoadSize+=recvCount;
			}
		}
		recvCount=splice((*pcur)->new_fd,NULL,fds[1],NULL,fileSize-downLoadSize,SPLICE_F_MORE | SPLICE_F_MOVE);
		ERROR_CHECK(recvCount,-1,"splice1");
		recvCount=splice(fds[0],NULL,fd,NULL,recvCount,SPLICE_F_MORE | SPLICE_F_MOVE);
		ERROR_CHECK(recvCount,-1,"splice2");
		gettimeofday(&end,NULL);
		//接结束符
		int ret=recvCycle((*pcur)->new_fd,(char*)&dataLen,sizeof(int));
		if(-1==ret)
		{
			printf("recv error\n");
		}
		printf("use time=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
		close(fd);
		close((*pcur)->new_fd); 
    }else{
        t.dataLen=2*sizeof(char);
        strcpy(t.buf,"-1");
        sendCycle((*pcur)->new_fd,(char*)&t,4+t.dataLen);
    }
	return 0;
}

