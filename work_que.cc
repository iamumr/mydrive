#include "include/work_que.h"
#include "include/Epoll.h"

void task::set_data(void* data)
{
    m_ptr_data=data;
    Mylogger::getInstance()->error("数据传递 %d",*(int*)data);
}

int mytask::Run()    
{
        Mylogger::getInstance()->info("开始任务处理");
        int i=*(int*)m_ptr_data;
        trans_control t;
        t.set_data(i);
        t.rec();
        
        /* trans_control s; */
        /* char buf[2000]="do the best"; */
        /* s.set_data(i,3,3333,buf); */
        /* s.sen(); */

        Epoll::getInstance()->del(i);
        /* close(i); */
        return 0;
    }
