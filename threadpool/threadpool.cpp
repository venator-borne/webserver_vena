//
// Created by Administrator on 2024/6/15.
//

#include "threadpool.h"
#include <iostream>

#ifdef __linux__
  #include <unistd.h>
#elif _WIN32
  #include <Windows.h>
#endif

template<typename T>
threadpool<T>::threadpool() {
  int threadpool_num = 8;
  #ifdef __linux__
    threadpool_num = sysconf(_SC_NPROCESSORS_ONLN);
  #elif _WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    threadpool_num = sysinfo.dwNumberOfProcessors;
  #endif
  
  int max_requests = 10000;

  threadpool(threadpool_num, max_requests);
}

template<typename T>
threadpool<T>::threadpool(int threadpool_num, int max_requests) {
  if(threadpool_num < 1 || max_requests < 0) throw std::exception();

  stop_pool = false;

  threads = new pthread_t[threadpool_num];
  if(!threads) throw std::exception();

  for (size_t i = 0; i < threadpool_num; i++) {
    std::cout << "create num" << i << " thread in pool" << std::endl;
    if(pthread_create(threads+i, nullptr, work, this) != 0) {
      delete[] threads;
      throw std::exception();
    }

    if(pthread_detach(threads[i])) {
      delete[] threads;
      throw std::exception();
    }
  }
}

template<typename T>
threadpool<T>::~threadpool() {
  delete[] threads;
  stop_pool = true;
}

template<typename T>
bool threadpool<T>::append(T* request) {
  queuelock.lock();
  if(workqueue.size() > max_queue_num) {
    queuelock.unlock();
    return false;
  }

  workqueue.push_back(request);
  queuelock.unlock();
  //发布一个可供线程池消耗的资源
  queue_sema.post();
  return true;
}

template<typename T>
void* threadpool<T>::work(void *arg) {
  threadpool* pool = (threadpool)arg;
  pool->run();
  return pool;
}

template<typename T>
void threadpool<T>::run() {
  while (!stop_pool) {
    //等待任务到来
    queue_sema.wait();

    //获取一个任务
    queuelock.lock();
    //双校验锁机制
    if(workqueue.empty()) {
      queuelock.unlock();
      continue;
    }

    T* req = workqueue.front();
    workqueue.pop_front();
    queuelock.unlock();

    if(req == nullptr) continue;
    req->process();
  }
}