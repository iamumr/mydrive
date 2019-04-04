#define _GNU_SOURCE
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
#include <openssl/md5.h>
#include "openssl/sha.h"
#include <mysql/mysql.h>
#define SALT_STR_LEN 10
#define TOKEN_LEN 20
#define THREAD_NUM 30
#define QUE_NUM 100
#define LISTEN_IP "192.168.5.208"
#define LISTEN_PORT "8888"
int mysqlQuery(char *que);
int GenerateStr(char*);
int passedSHA512(unsigned char *passwd,int len,char *salt);
int userReg(char*,char*,unsigned char*,char*,char*);
int mysqlUsername(char *username,char *salt,char *passwd,char*);//依靠用户名查询salt和密码，用户登入使用
int MD5Token(int num,char* tmp,...);
#define args_check(argc,num) {if(argc!=num) {printf("error args\n");return -1;}}
#define ERROR_CHECK(ret,retval,funcname) {if(ret==retval) {perror(funcname);return -1;}}
#define THREAD_ERROR_CHECK(ret,funcname) {if(ret != 0) {printf("%s failed %s\n",funcname,strerror(ret));return -1;}}
#define FILENAME "file"
