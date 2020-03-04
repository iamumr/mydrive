#ifndef __FUNC_H__
#define __FUNC_H__

#include "Epoll.h"
#include "tcp.h"
#include "factory.h"
#include "logger.h"
#include "transfile.h"
#include "work_que.h"

//linux
#include <sys/mman.h>
#include <errno.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <sys/msg.h>
#include <strings.h>
#include <syslog.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

//openssl
#include <openssl/md5.h>
#include "openssl/sha.h"

//mysql
#include "mysql/mysql.h"
#include<stdarg.h>

//c++库
#include <iostream>
#include <deque>
#include <string>
#include <map>
#include <memory>

#define SALT_STR_LEN 10
#define TOKEN_LEN 20
#define THREAD_NUM 30
#define QUE_NUM 100
#define LISTEN_IP "172.17.23.240"
#define LISTEN_PORT "8889"
#define WORK_DIR "/tmp/mydrive"


#define args_check(argc,num) {if(argc!=num) {printf("error args\n");return -1;}}
#define ERROR_CHECK(ret,retval,funcname) {if(ret==retval) {perror(funcname);return -1;}}
#define THREAD_ERROR_CHECK(ret,funcname) {if(ret != 0) {printf("%s failed %s\n",funcname,strerror(ret));return -1;}}
#define FILENAME "file"

#endif
