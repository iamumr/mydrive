#include "include/Epoll.h"

Epoll Epoll::_epoll_instance;
int Epoll::_epfd;
/* tcp Epoll::_tcp; */
factory Epoll::_factory(20);

Epoll* Epoll::getInstance()
{

    /* if(!_epoll_instance) */
    /* { */
    /*     _epoll_instance=new Epoll(); */
    /*     /1* Mylogger::getInstance()->error("null"); *1/ */
    /* } */
    /* return _epoll_instance; */
    
    return &_epoll_instance;
}

void Epoll::destory()
{
    /* if(_epoll_instance) */
        /* delete _epoll_instance; */
}

bool Epoll::add(int fd,uint32_t events)
{
    struct epoll_event ev;
    ev.events=events;
    ev.data.fd=fd;

    int ret=epoll_ctl(this->_epfd,EPOLL_CTL_ADD,fd,&ev);
    if(ret<0)
    {
        Mylogger::getInstance()->error("epoll add error.");
        return false;
    }
    Mylogger::getInstance()->info("监听%d",fd);
    return true;
}

bool Epoll::del(int fd)
{
    int ret=epoll_ctl(this->_epfd,EPOLL_CTL_DEL,fd,NULL);
    //取消注册也要删除，否则会一直占用序号
    close(fd);
    if(ret<0)
    {
        Mylogger::getInstance()->error("epoll del error.");
        return false;
    }
    return true;
}

bool Epoll::mod(int fd,uint32_t events)
{
    struct epoll_event ev;
    ev.data.fd=fd;
    ev.events=events;
    int ret=epoll_ctl(this->_epfd,EPOLL_CTL_MOD,fd,&ev);
    if(ret<0)
    {
        Mylogger::getInstance()->error("epoll mod error");
        return false;
    }
    return true;
}

bool Epoll::wait(int ms_timout)
{
    struct epoll_event events[20];
    for(;;)
    {
        int nfds=epoll_wait(this->_epfd,events,20,ms_timout);
        for(int i=0;i<nfds;i++)
        {
            if(events[i].data.fd==this->_tcp->get_sfd())
            {//新连接，加入epoll监听
                int new_fd=this->_tcp->tcp_accept();
                setnoblocking(new_fd);
                add(new_fd,EPOLLIN);

            /* }else if(events[i].events&(EPOLLIN|EPOLLHUP)){ */
            /*     //对端关闭，关闭连接，取消监听 */
            /*     del(events[i].data.fd); */
            /*     close(events[i].data.fd); */
            /*     Mylogger::getInstance()->info("remote connect closed"); */

            }else if(events[i].events&EPOLLIN){
                //连接有数据可读，加入任务队列
                mytask* tmp=new mytask();
                Mylogger::getInstance()->error("fd is %d",events[i].data.fd);
                int *t=new int;
                *t=events[i].data.fd;
                tmp->set_data((void*)t);
                _factory.add_task((task*)tmp);
                /* del(*t); */
                Mylogger::getInstance()->info("新建任务");
            }else if(events[i].events&EPOLLOUT){
                /* trans_file* tmp=new trans_file; */
                
                /* _factory->add_task(tmp); */
            }else{

            }
        }
    }
}

Epoll::Epoll()
{

    _epfd=epoll_create(1);
    if(_epfd<0)
    {
        Mylogger::getInstance()->error("epoll init error.");
    }
    _tcp=new tcp();

    setnoblocking(this->_epfd);
    add(_tcp->get_sfd(),EPOLLIN);
    Mylogger::getInstance()->info("初始化完成，%d",_tcp->get_sfd());
    /* _factory=new factory(20); */

}

bool Epoll::setnoblocking(int sock)
{
    int opts=fcntl(sock,F_GETFL);
    if(opts<0)
    {
        Mylogger::getInstance()->error("fcntl(sock,F_GETFL) error");
        return false;
    }
    opts|=O_NONBLOCK;
    if(fcntl(sock,F_SETFL,opts)<0)
    {
        Mylogger::getInstance()->error("fcntl setfl error");
        return false;
    }
    return true;
}

Epoll::~Epoll()
{
    
}
