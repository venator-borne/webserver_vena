#ifndef LOCKER_H
#define LOCKER_H


#include <exception>
#include <pthread.h>
#include <semaphore.h>


/**
 * 互斥锁
 * 临界区,共享变量,原子性
*/
class locker
{
private:
  pthread_mutex_t mutex_lock;
public:
  locker(/* args */);
  ~locker();

  bool lock();
  bool unlock();

  pthread_mutex_t* getLock() {
    return &mutex_lock;
  }
};

#endif