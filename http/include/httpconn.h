#ifndef HTTP_CONN_H
#define HTTP_CONN_H

#include <iostream>

#include "../buffer/buffer.h"

class httpconn
{
private:
  buffer readbuff_;
  buffer writebuff_;
  
public:
  httpconn(/* args */);
  ~httpconn();

  void init();
  ssize_t read();
  ssize_t write();
  void close();
};

#endif
