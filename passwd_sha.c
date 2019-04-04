#include "include/func.h"
//生成slat值
int GenerateStr(char *tmp)
{
    //char str[SALT_STR_LEN+1]={0};
    int i,flag;
    srand(time(NULL));
    for(i=0;i<SALT_STR_LEN;++i)
    {
        flag=rand()%3;
        switch(flag)
        {
        case 0:
            tmp[i]=rand()%26+'a';
            break;
        case 1:
            tmp[i]=rand()%26+'A';
            break;
        case 2:
            tmp[i]=rand()%10+'0';
            break;
        }
    }
    //printf("%s\n",str);
    return 0;
}
//SHA512加密
int passedSHA512(unsigned char *passwd,int len,char *salt)
{
    SHA512_CTX stx; 
    SHA512_Init(&stx);
    SHA512_Update(&stx,passwd,len);
    SHA512_Update(&stx,salt,SALT_STR_LEN);
    unsigned char sha[64]; 
    SHA512_Final(sha,&stx);
    //printf("%hhn\n",sha);
    //for(int i=0;i<64;i++)
    //{
    //    printf("%02x",sha[i]);
    //}
    memcpy(passwd,sha,64);
    //printf("\n");
}

