#include "include/transfile.h"

int trans::sendCycle()
{
    int total=0;
    while(total<len)
    {
        int ret;
        if((ret=send(this->new_fd,(char*)buf+total,this->len-total,0))==-1)
        {
            return -1;
        }
        total+=ret;
    }
    Mylogger::getInstance()->info("发送完成");
    return 0;
}

int trans::recvCycle()
{
    int total=0;
    int ret;
    Mylogger::getInstance()->info("准备接收");
    while(total<this->len)
    {
        ret=recv(new_fd,(char*)buf+total,this->len-total,0);
        total+=ret;
        Mylogger::getInstance()->debug("已接收%d",total);
    }
    Mylogger::getInstance()->info("接收完成");
    return 0;
}

int trans_control::sen()
{
    len=sizeof(m);
    buf=(char*)&m;
    sendCycle();
    Mylogger::getInstance()->info("状态回复完成");
    return 0;
}

int trans_control::rec()
{
    Mylogger::getInstance()->info("接收控制字符");
    len=sizeof(node);
    buf=(char*)&m;
    memset(&m,0,sizeof(m));
    recvCycle();
    Mylogger::getInstance()->info("get messages %s",m.mess);
    return 0;
}
    
void trans_control::set_data(int fd)
{
    memset(&m,0,sizeof(node));
    new_fd=fd;
    buf=(char*)&m;
    len=sizeof(node);
}
void trans_control::set_data(int fd,int control,int token,char* mm)
{
    memset(&m,0,sizeof(node));
   this->new_fd=fd;
   this->m.control=control;
   this->m.token=token;
   strcpy(this->m.mess,mm);
   Mylogger::getInstance()->info("写入控制数据%s",mm);
   len=sizeof(node);
   buf=(char*)&m;
}


