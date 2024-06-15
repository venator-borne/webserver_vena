#include <iostream>
#include "condition.h"

condition::condition(/* args */) {
  if(pthread_cond_init(&(this->cond_lock), NULL) != 0) throw std::exception();
}

condition::~condition() {
  pthread_cond_destroy(&(this->cond_lock));
}

bool condition::wait(pthread_mutex_t *mutex) {
  return pthread_cond_wait(&(this->cond_lock), mutex) == 0;
}

bool condition::wait(pthread_mutex_t *mutex, struct timespec t) {
  return pthread_cond_timedwait(&(this->cond_lock), mutex, &t) == 0;
}

bool condition::signal(pthread_mutex_t *mutex) {
  return pthread_cond_signal(&cond_lock) == 0;
}

bool condition::broadcast() {
  return pthread_cond_broadcast(&cond_lock);
}