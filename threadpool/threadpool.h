#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <exception>
#include <pthread.h>
#include <semaphore.h>
#include <list>
#include "locker.h"
#include <iostream>
#include "sema.h"

template <typename T>
class threadpool
{
private:
  int pthread_num;
  pthread_t *threads;
  int max_queue_num;
  std::list<T*> workqueue;

  locker queuelock;
  sema queue_sema;

  bool stop_pool;
public:
  threadpool(/* args */);
  threadpool(int threadpool_num, int max_requests); 
  ~threadpool();

  //向工作队列添加任务,注意线程同步
  bool append(T* request);
private:
  static void* work(void *arg);
  void run();
};


#endif