#include "include/func.h"

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

