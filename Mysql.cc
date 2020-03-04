#include "include/Mysql.h"
#include "include/logger.h"


Mysql::Mysql(const char* server,const char* user,const char* pwd,const char* db,int port)
{
    _conn=mysql_init(NULL);
    if(!mysql_real_connect(_conn,server,user,pwd,db,port,0,0))
    {
        Mylogger::getInstance()->error("mysql connect error");
    }else{
        Mylogger::getInstance()->info("mysql connected");
    }
}

Mysql::~Mysql()
{
    mysql_close(_conn);
}

bool Mysql::write_data(std::string query)
{
    if(mysql_query(_conn,query.c_str()))
    {
        Mylogger::getInstance()->info("write failed");
        return false;
    }else{
        Mylogger::getInstance()->error("write sucess");
        return true;
    }
}

bool Mysql::create_table(const std::string &query)
{
    if(0==mysql_query(_conn,query.c_str()))
    {
        return true;
    }
    return false;
}

bool Mysql::get_data(std::string query,std::vector<std::vector<std::string>>&data)
{
    if(0!=mysql_query(_conn,query.c_str()))
    {
        Mylogger::getInstance()->error("get data failed,%d %s",mysql_errno(_conn),mysql_error(_conn));
        return false;
    }
    _res=mysql_store_result(_conn);
    int row=mysql_num_rows(_res);
    int field=mysql_num_fields(_res);
    
    MYSQL_ROW line=NULL;
    line=mysql_fetch_row(_res);

    std::string temp;
    while(NULL!=line)
    {
        std::vector<std::string> line_data;
        for(int i=0;i<field;i++)
        {
            if(line[i])
            {
                temp=line[i];
            }else{
                temp="";
            }
            line_data.push_back(temp);
        }
        line=mysql_fetch_row(_res);
        data.push_back(line_data);
    }
    return true;
}
