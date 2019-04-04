#include "include/factory.h"

int MD5Token(int num,char* tmp,...)
{
    MD5_CTX ctx;
    unsigned char md5[16];
    MD5_Init(&ctx);
    char *str=tmp;
    va_list ap;
    va_start(ap,tmp);
    for(int i=0;i<num;i++)
    {

        MD5_Update(&ctx,str,strlen(str));
        str=va_arg(ap,char*);
    }
    MD5_Final(md5,&ctx);
    va_end(ap);
    memset(tmp,0,sizeof(*tmp));
    int len=0;
    for(int i=0;i<16;i++)
    {
        len+=sprintf(tmp+len,"%x",md5[i]);
    }
    return 0;
}
