#include "include/tcp.h"
int tcp::tcp_init(sockaddr_in* socks)
{
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==sfd)
    {
        cerr<<"socket"<<endl;
        exit(-1);
    }
    if(bind(sfd,(struct sockaddr*)socks,sizeof(struct sockaddr_in))==-1)
    {
        cerr<<"bind"<<endl;
        close(sfd);
        exit(-1);
    }
    if(listen(sfd,10)==-1)
    {
        cerr<<"listen"<<endl;
        close(sfd);
        exit(-1);
    }
    this->sfd=sfd;
    return sfd;
}

int tcp::tcp_accept()
{
    struct sockaddr_in clientaddr;
    memset(&clientaddr,0,sizeof(sockaddr_in));
    int addrlen=sizeof(sockaddr);
    int new_fd=accept(sfd,(struct sockaddr*)&clientaddr,(socklen_t*)&addrlen);
    if(-1==new_fd)
    {
        cerr<<"accept"<<endl;
        close(sfd);
        exit(-1);
    }
    return new_fd;
}

int tcp::tcp_connect(const char* ip,int port)
{
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==sfd)
    {
        cerr<<"socker"<<endl;
        exit(-1);
    }
    struct sockaddr_in serveraddr;
    memset(&serveraddr,0,sizeof(sockaddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=inet_addr(ip);
    if(connect(sfd,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr))==-1)
    {
        cerr<<"connect"<<endl;
        close(sfd);
        exit(-1);
    }
    return sfd;
}

int tcp::get_sfd()
{
    return sfd;
}

tcp::tcp()
{
}
tcp::tcp(const char* i,int port)
{
    inet_pton(AF_INET,i,&socks.sin_addr);
    socks.sin_family=AF_INET;
    socks.sin_port=htons(port);
    tcp_init(&socks);
}
