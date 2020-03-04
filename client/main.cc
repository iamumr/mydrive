#include "include/tcp.h"
#include "include/func.h"
using namespace std;
struct node{
    int control;
    int token;
    char mess[2000];
}m;
int main()
{
    tcp test;
    char ip[]="127.0.0.1";
    int new_fd=test.tcp_connect(ip,1025);
    cout<<new_fd<<endl;
    unsigned long total=0;
    m.control=100;
    m.token=200;
    strcpy(m.mess,"keep going");
    int ret;
    while(total<sizeof(m))
    {
        ret=send(new_fd,(char*)&m+total,sizeof(m)-total,0);
        total+=ret;
        cout<<total<<endl;
    }
    total=0;
	while(total<sizeof(m))
	{
		ret=recv(new_fd,(char*)&m+total,sizeof(m)-total,0);
		total=total+ret;
	}    
    cout<<m.mess<<endl;
    sleep(1);
    ret=read(new_fd,(char*)&m,sizeof(m));
    cout<<ret<<endl;
    if(0==ret) close(new_fd);
    /* int opt_val; */
    /* socklen_t opt_len=sizeof(opt_val); */
    /* cout<<getsockopt(new_fd,IPPROTO_TCP,TCP_INFO,opt_val,opt_len)<<endl; */
    while(1);
    return 0;
}

