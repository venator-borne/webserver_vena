#include "locker.h"

locker::locker() {
  /*
    第二个参数attr指向互斥量相关属性,一般为null
  */
  if(pthread_mutex_init(&(this->mutex_lock), NULL) != 0) throw std::exception();
}

locker::~locker() {
  pthread_mutex_destroy(&(this->mutex_lock));
}

bool locker::unlock() {
  return pthread_mutex_unlock(&(this->mutex_lock)) == 0;
}

bool locker::lock() {
  return pthread_mutex_lock(&(this->mutex_lock)) == 0;
}