#include "include/factory.h"

int userReg(char *user_login,char *user_salt,unsigned char *user_pass,char *user_email,char *display_name)
{
	char query[2000]={0};
	sprintf(query,"INSERT INTO `users` (`user_login`, `user_salt`, `user_pass`, `user_email`, `user_status`, `display_name`) VALUES ('%s', '%s', '%s', '%s', '0', '%s')",user_login,user_salt,user_pass,user_email,display_name);
	int t=mysqlQuery(query);
	if(0==t)
	{
		printf("用户创建成功");
		return 0; //success
	}else{
		printf("用户创建失败，请联系管理员！");
		return -1;//fail 
	}
}
int userCreat(pNode_t* pcur)
{
	fflush(stdout);//case后不允许直接跟变量定义加的无用语句 
	//生成salt并返回客户端 
	char str[SALT_STR_LEN+1];
	GenerateStr(str);
	train t;
	t.dataLen=strlen(str);
	strcpy(t.buf,str);
	sendCycle((*pcur)->new_fd,(char*)&t,4+t.dataLen);
	puts(str); 
	//接收密文密码 
	recvCycle((*pcur)->new_fd,(char*)&t.dataLen,sizeof(int));
	printf("%d\n",t.dataLen); 
	memset(t.buf,0,sizeof(t.buf)); 
	recvCycle((*pcur)->new_fd,(char*)t.buf,t.dataLen);
	char pass[128]={0};
	strcpy(pass,t.buf);
	//printf("%s\n",t.buf); 
	puts(pass); 
	//接收邮箱
	recvCycle((*pcur)->new_fd,(char*)&t.dataLen,sizeof(int));
	memset(t.buf,0,sizeof(t.buf));
	recvCycle((*pcur)->new_fd,(char*)t.buf,t.dataLen);
	char email[255]={0};
	strcpy(email,t.buf);
	puts(email);
	//接收昵称
	recvCycle((*pcur)->new_fd,(char*)&t.dataLen,sizeof(int));
	memset(t.buf,0,sizeof(t.buf));
	recvCycle((*pcur)->new_fd,(char*)t.buf,t.dataLen);
	char nickname[255]={0};
	strcpy(nickname,t.buf);
	//创建用户并返回状态
	int stat=userReg((*pcur)->dir,str,(unsigned char*)pass,email,nickname);
	memset(t.buf,0,sizeof(t.buf));
	//itoa(stat,t.buf,10);
	sprintf(t.buf,"%d",stat);
	t.dataLen=sizeof(t.buf);
	sendCycle((*pcur)->new_fd,(char*)&t,4+t.dataLen);
}
int userLogin(pNode_t* pcur)
{
    char salt[SALT_STR_LEN+1]={0};
    char passwd[128]={0};
    char user_id[20];
    mysqlUsername((*pcur)->dir,salt,passwd,user_id);
    train t;
    //返回salt值
    t.dataLen=strlen(salt);
    strcpy(t.buf,salt);
    sendCycle((*pcur)->new_fd,(char*)&t,4+t.dataLen);
    //接收密文密码
    recvCycle((*pcur)->new_fd,(char*)&t.dataLen,sizeof(int));
    recvCycle((*pcur)->new_fd,(char*)&t.buf,t.dataLen);
    //比对并返回
    char user_name[255]={0};
    strcpy(user_name,(*pcur)->dir);
    time_t curtime;
    time(&curtime);
    MD5Token(2,user_name,salt,ctime(&curtime));
    t.dataLen=strlen(user_name);
    memset(t.buf,0,sizeof(t.buf));
    strcpy(t.buf,user_name);
    sendCycle((*pcur)->new_fd,(char*)&t,4+t.dataLen);
    //数据库保存token信息
    char query[2000]={0};
    sprintf(query,"INSERT INTO `user_token`(`user_id`,`user_token`,`expir_time`) VALUES('%s','%s','%ld')",user_id,user_name,time(NULL)+86400);
    int tmp=mysqlQuery(query);
    if(0==tmp)
    {
        printf("客户端登入成功\n");
        return 0;
    }else{
        printf("登入失败，请重新检查\n");
        return -1;
    }
}

