#ifndef __EPOLL_H__
#define __EPOLL_H__

#include <stdint.h>
#include <sys/epoll.h>
#include "tcp.h"
#include "work_que.h"
#include "factory.h"

class Epoll
{
public:
    bool add(int fd,uint32_t events=EPOLLIN);
    bool del(int fd);
    bool mod(int fd,uint32_t events=EPOLLOUT);
    bool wait(int ms_timeout=0);
    static Epoll * getInstance();
    static void destory();

private:
    Epoll();
    ~Epoll();

private:
    static Epoll _epoll_instance;
    bool setnoblocking(int sock);
    static int _epfd;
    tcp*  _tcp;    
    static factory  _factory; 
};

#endif
