#include "buffer.h"
#include <assert.h>
#include <algorithm>
#include <iterator>

buffer::buffer(int initBufferSize) : buffer_(initBufferSize), readIndex(0), writeIndex(0) {}

size_t buffer::writablebytes() const {
  return buffer_.size() - writeIndex;
}

size_t buffer::readablebytes() const {
  return writeIndex - readIndex;
}

size_t buffer::prependablebytes() const{
  return readIndex;
}

void buffer::ensurewritable(size_t len) {
  if (len > writablebytes())
  {
    makespace(len);
  }
  assert(len <= writablebytes());
} 

//TODO: 为什么会存在这两个函数???
char* buffer::beginptr_() {
    return &buffer_[0];
}

const char* buffer::beginptr_() const{
    return &buffer_[0];
}

/**
 * 写入大于剩余空间: 扩容vector
 * 写入小于剩余空间: 前移读数据, 重塑vector, 空间大小不变
*/
void buffer::makespace(size_t len) {
  if(writablebytes() + prependablebytes() < len) {
    buffer_.resize(writeIndex + len + 1);
  } else {
    std::copy(buffer_.begin() + readIndex, buffer_.begin() + writeIndex, buffer_.begin());
    writeIndex = readablebytes();
    readIndex = 0;
    assert(readIndex == readablebytes());
  }
}