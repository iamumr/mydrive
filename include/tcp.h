#ifndef __TCP_H__
#define __TCP_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>

#include "logger.h"

using namespace std;

class tcp
{
public:
    tcp();
    tcp(int port);
    tcp(const char* i,int port);
    /* ~tcp(); */
    int tcp_init(sockaddr_in*);
    int tcp_accept();
    int tcp_connect(const char* ip,int port);
    int get_sfd();
private:
    sockaddr_in socks;//套接字
    int sfd;
};

#endif
