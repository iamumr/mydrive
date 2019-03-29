#include "include/func.h"

int main()
{
    char str[SALT_STR_LEN+1]={0};
    GenerateStr(str);
    printf("%s\n",str);
    char passwd[64]="hahahaha";
    passedSHA512(passwd,8,str); 
    return 0;
}

