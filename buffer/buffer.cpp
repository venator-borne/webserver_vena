#include "buffer.h"

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
  if (len > writablebytes()) {
    makespace(len);
  }
  assert(len <= writablebytes());
} 

void buffer::haswritten(std::size_t len) {
    writeIndex += len;
}

void buffer::hasread(std::size_t len) {
    readIndex += len;
}

const char * buffer::getreadindex() const{
  return &(buffer_[readIndex]);
}

const char * buffer::getwriteindex() const{
    return &(buffer_[writeIndex]);
}

char* buffer::readpeek() {
  return &(buffer_[readIndex]);
}

char* buffer::writepeek() {
  return &(buffer_[writeIndex]);
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

/**
* 一系列的append方法，用于向缓冲区添加数据
* 有像是str字符串, 
*/
void buffer::append(const std::string& str) {
    append(str.c_str(), str.size());
}
void buffer::append(const char* str, size_t len) {
    assert(str);
    ensurewritable(len);
    std::copy(str, str + len, buffer_[writeIndex]);
    haswritten(len);
}
void buffer::append(const void* data, size_t len) {
    //将任意类型指针转换为字符数组方式访问
    append(static_cast<const char *>(data), len);
}
void buffer::append(const buffer& buff) {
    //返回buff中所有可读数据, 因为是const对象 只能访问const成员寒素
    append(buff.getreadindex(), buff.writablebytes());
}

/**
* 正式读写部分
 * readfd: 从fd读到buffer
 * write: 从buffer读到fd
 *
 * 系统调用:
 * readv用于从文件描述符(文件/套接字)中读取数据到多个缓冲区中, 参数:
 * fd 是文件描述符，指定从哪个文件或套接字读取数据。
 * iov 是一个指向 struct iovec 数组的指针，每个 struct iovec 描述了一个缓冲区的位置和大小。
 * iovcnt 是 iov 数组中 struct iovec 的数量，即缓冲区的个数。
 * 成功读取的字节数，如果返回值为0，则表示已到达文件末尾。
*/
ssize_t buffer::readfd(int fd, int *Errno) {
    size_t len = writablebytes();
    struct iovec iov[2]; //创建一个备用缓冲区, 以免数据不够存放
    char buff[65536];
    iov[0].iov_base = readpeek();
    iov[0].iov_len = len;

    iov[1].iov_base = buff;
    iov[1].iov_len = sizeof(buff);

    ssize_t f = readv(fd, iov, 2);
    if(f < 0) {
        *Errno = errno;
    } else if (static_cast<size_t>(f) <= len) {
        haswritten(static_cast<size_t>(f));
    } else {
        haswritten(len);
        append(buff, static_cast<size_t>(f) - len);
    }

    return f;
}

ssize_t buffer::writefd(int fd, int* Errno) {
    ssize_t len = write(fd, getreadindex(), readablebytes());
    if(len < 0) {
        *Errno = errno;
    } else hasread(len);
    return len;
}