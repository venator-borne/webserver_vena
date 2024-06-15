#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <atomic>

class buffer
{
private:
  std::vector<char> buffer_;
  std::atomic<size_t> readIndex;
  std::atomic<size_t> writeIndex;

public:
  buffer(int initBufferSize = 1024);
  ~buffer() = default;

  
  size_t writablebytes() const; //可写多少bytes
  size_t readablebytes() const; //可读多少bytes
  size_t prependablebytes() const; //预留多少bytes(已经读过去多少bytes)
  void ensurewritable(size_t len); //是否可写
  
  ssize_t readfd(int fd, int *errno); //将fd中数据读入到buffer中, 涉及到writeIndex的移动
  ssize_t writefd(int fd, int* errno); //将buffer中数据写入到fd当中, 涉及到readIndex的移动

  //移动写下标
  // void 
  //移动读下标

private:
  char* beginptr_();
  const char* beginptr_() const;
  void makespace(size_t len); //扩展空间
};

#endif