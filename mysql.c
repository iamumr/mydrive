#include "include/func.h"

int mysqlQuery(char *que) //标准查询，输入任何mysql语句，返回是否实行成功
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server="localhost";
    char *user="root";
    char* password="liliyang1995";
    char* database="mydrive";
    conn=mysql_init(NULL);
    if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
    {
        printf("Error connecting to database:%s\n",mysql_error(conn));
    }
    int t=mysql_query(conn,que);
    if(t)
    {
        mysql_close(conn);
        return -1;//查询失败
    }
    else
    {
        mysql_close(conn);
        return 0;//查询成功
    }
}

int mysqlUsername(char *username,char *salt,char *passwd,char *user_id)//输入char参数，获取salt及密码
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server="localhost";
    char *user="root";
    char* password="liliyang1995";
    char* database="mydrive";
    conn=mysql_init(NULL);
    if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
    {
        printf("Error connecting to database:%s\n",mysql_error(conn));
    }
    char query[2000]={0};
    sprintf(query,"select * from users where user_login = '%s'",username);
    int t=mysql_query(conn,query);
    if(t){
        return -1;//查询失败
    }else{
        res=mysql_use_result(conn);
        if(res)
        {
            while((row=mysql_fetch_row(res))!=NULL)
            {
                strcpy(salt,row[2]);
                strcpy(passwd,row[3]);
                strcpy(user_id,row[0]);
            }
        }else{
            mysql_free_result(res);
            return 1;//查询成功但用户不存在
        }
        mysql_free_result(res);
        return 0;//查询成功
    }
}
