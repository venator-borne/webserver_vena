#ifndef SEMA_H
#define SEMA_H
#include <exception>
#include <pthread.h>
#include <semaphore.h>

class sema
{
private:
  sem_t m_sem;
public:
  sema();
  sema(int num);
  ~sema();

  bool wait();
  bool post();
};

#endif