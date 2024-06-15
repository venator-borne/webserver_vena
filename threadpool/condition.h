#include <exception>
#include <pthread.h>
#include <semaphore.h>


/**
 * 条件变量
 * 等待事件发生
*/
class condition
{
private:
  pthread_cond_t cond_lock;
public:
  condition(/* args */);
  ~condition();

  bool wait(pthread_mutex_t *mutex);
  bool wait(pthread_mutex_t *mutex, struct timespec t);

  //用于唤醒一个到多个线程
  bool signal(pthread_mutex_t *mutex);
  
  //用于唤醒所有等待线程
  bool broadcast();
};


