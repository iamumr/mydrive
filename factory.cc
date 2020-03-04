#include "include/factory.h"
#include "include/Epoll.h"

factory::factory(int threadnum)
{
   this->m_thread_num=threadnum;
   pthread_mutex_init(&this->m_mutex,NULL);
   pthread_cond_init(&this->m_cond,NULL);
   this->shutdown=false;

   Mylogger::getInstance()->error("准备创建线程");
   create();
}

int factory::create()
{
    this->pthread_id=new pthread_t[this->m_thread_num];
    for(int i=0;i<this->m_thread_num;i++)
    {
        pthread_create(&pthread_id[i],NULL,thread_func,(void*)this);
    }
    Mylogger::getInstance()->error("线程池创建完成");
    return 0;
}

void* factory::thread_func(void* thread_data)
{
    pthread_t tid=pthread_self();//获得自身线程编号
    factory* t_this=(factory*)thread_data;
    Mylogger::getInstance()->info("进入线程，编号%d",tid);
    while(1)
    {
        pthread_mutex_lock(&t_this->m_mutex);
        while(t_this->m_task_list.size()==0&&!t_this->shutdown)
        {
            Mylogger::getInstance()->info("线程等待中");
            pthread_cond_wait(&t_this->m_cond,&t_this->m_mutex);
        }   
        
        if(t_this->shutdown)
        {
            pthread_mutex_unlock(&t_this->m_mutex);
            Mylogger::getInstance()->error("%d exit.",tid);
            pthread_exit(NULL);
        }
        Mylogger::getInstance()->info("%d run",tid);
        mytask* t_task=(mytask*)t_this->m_task_list.front();
        t_this->m_task_list.pop_front();
        pthread_mutex_unlock(&t_this->m_mutex);
        t_task->Run();
    }
}

int factory::add_task(task* t_task)
{
    pthread_mutex_lock(&this->m_mutex);
    this->m_task_list.push_back(t_task);
    pthread_mutex_unlock(&this->m_mutex);
    pthread_cond_signal(&this->m_cond);
    Mylogger::getInstance()->info("任务入队");
    return 0;
}

int factory::stop_all()
{
    if(this->shutdown)
        return -1;
    Mylogger::getInstance()->info("pthread poll will be ended.\n");
    this->shutdown=true;
    pthread_cond_broadcast(&this->m_cond);
    for(int i=0;i<this->m_thread_num;i++)
    {
        pthread_join(this->pthread_id[i],NULL);
    }
    delete []this->pthread_id;
    this->pthread_id=NULL;
    pthread_mutex_destroy(&this->m_mutex);
    pthread_cond_destroy(&this->m_cond);

    return 0;
}

int factory::get_task_size()
{
    return this->m_thread_num;
}

factory::~factory()
{

}

