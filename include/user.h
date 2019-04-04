#include "func.h"
typedef struct{
    int userID;
    char salt[SALT_STR_LEN+1];
    char passSHA[64];
    char token[TOKEN_LEN];
}user;
