#include "include/func.h"
#include "include/Mysql.h"

using namespace std;
int main()
{
    chdir(WORK_DIR);

    /* tcp mm_tcp; */
    /* drive::factory thread_poll(10); */

    /* drive::mytask test; */
    /* char tmp[6]="hello"; */
    /* test.set_data((void*)&tmp); */
    /* Mylogger::getInstance()->error("准备传数据"); */
    /* for(int i=0;i<10;i++) */
    /* { */
    /*     thread_poll.add_task(&test); */
    /*     Mylogger::getInstance()->error("%d组任务进度",i); */
    /* } */
    
    /* while(1) */
    /* { */
    /*     int new_fd=mm_tcp.tcp_accept(); */
    /*     drive::mytask* p_task=new drive::mytask; */ 
    /*     p_task->set_data((void*)&new_fd); */
    /*     thread_poll.add_task(p_task); */
    /* } */

    Epoll* epo=Epoll::getInstance();
    epo->wait(0);
    
    //测试mysql封装
    /* Mysql test("cdb-3i7n8j0i.bj.tencentcdb.com","root","lYl-19950627","wordpress",10013); */
    /* vector<vector<string>> tt; */
    /* test.get_data("select * from wp_users",tt); */
    /* cout<<tt[0][1]<<endl; */

    return 0;
}

