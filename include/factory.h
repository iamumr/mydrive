#ifndef __PTHREAD_H__
#define __PTHREAD_H__


#include "work_que.h"
#include <deque>


class factory
{
public:
    factory()=delete;
    factory(int threadnum);
    ~factory();
    void start();
    int stop_all();
    int get_task_size();
    int add_task(task* t_task);

protected:
    static void* thread_func(void* thread_data);
    int move_to_idle(pthread_t id);
    int move_to_busy(pthread_t id);
    int create();

private:
    std::deque<task*> m_task_list;
    bool shutdown;
    int m_thread_num;
    pthread_t* pthread_id;

    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
};

#endif
