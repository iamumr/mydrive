#pragma once
#ifndef __MMSQL_H__
#define __MMSQL_H__

#include "mysql/mysql.h"
#include <string>
#include <vector>

class Mysql
{
public:
    Mysql(const char* server,const char* user,const char* pwd,const char* db,int port);
    ~Mysql();
    bool create_table(const std::string& query);
    bool write_data(std::string query);
    bool get_data(std::string query,std::vector<std::vector<std::string>>& data);

private:
    MYSQL * _conn;
    MYSQL_RES *_res;
};

#endif
