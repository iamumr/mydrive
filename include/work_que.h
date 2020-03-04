#ifndef __WORK_QUE_H__
#define __WORK_QUE_H__

#include <string>
#include <iostream>
#include "transfile.h"
#include <sys/socket.h>
#include <unistd.h>

class task
{
protected:
    std::string m_task;
    void* m_ptr_data;
public:
    task()=default;
    task(std::string a):m_task(a),m_ptr_data(NULL){}
    virtual ~task() {}
    virtual int Run()=0;
    void set_data(void* data);

    
};

class mytask:public task
{
public:
    mytask()=default;
    int Run();
    ~mytask() {}
};

class task_file:public task
{
public:
    task_file()=default;
    int Run();
    ~task_file() {}
};

#endif

