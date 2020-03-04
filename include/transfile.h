#ifndef __TRANSFILE_H__
#define __TRANSFILE_H__

#include <iostream>
#include "logger.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <memory.h>

class trans
{
public:
    trans() =default;
    ~trans() {}
    trans(int fd):new_fd(fd),len(0),buf(NULL){}
    int sendCycle();
    int recvCycle();
    virtual int sen()=0;
    virtual int rec()=0;

protected:
    int new_fd;
    int len;
    char *buf;
};

class trans_file:public trans
{
public:
    trans_file()=default;
    int se()
    {

    }

private:
    
};

class trans_control:public trans
{
public:
    trans_control()=default;
    void set_data(int fd,int control,int token,char* mm);
    void set_data(int fd);
    int sen();
    int rec();
private:
    struct node{
        int control;
        int token;
        char mess[2000];
    }m;
};

#endif
