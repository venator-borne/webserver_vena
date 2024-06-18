#ifndef EPOLL_CONNECTOR_H
#define EPOLL_CONNECTOR_H

#include <iostream>

class epoll_connector
{
private:
  /* data */
public:
  epoll_connector(/* args */);
  ~epoll_connector();

  void runsocket(); //初始化socket, 将接收到的套接字都交由epoll处理
  void runthreadpool(); //启动线程池
  
  void runlog(); //启动日志系统
};


#endif