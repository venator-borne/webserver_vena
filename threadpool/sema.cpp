#include "sema.h"

sema::sema(/* args */) {
  //pshared: 0线程间共享, !0进程间共享
  if(sem_init(&(this->m_sem), 0, 1) != 0) throw std::exception();
}

sema::sema(int num) {
  if(sem_init(&(this->m_sem), 0, num) != 0) throw std::exception();
}

sema::~sema() {
  sem_destroy(&(this->m_sem));
}

bool sema::wait() {
  return sem_wait(&(this->m_sem));
}
bool sema::post() {
  return sem_post(&(this->m_sem));
}