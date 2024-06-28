// 将该内存映射的指针加入buff，至此，报文的所有内容就都在buff中”，这句话说的并不对，mmap映射文件的指针没有加入buff，只是httpconn中处理请求的函数将ivo[1]的指针指向了这个文件
#ifndef RESPONSE_H
#define RESPONSE_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <unistd.h>
#include <assert.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/file.h>

#include "../config/server_cfg.h"
#include "../buffer/buffer.h"
/**
 * http报文格式
 *  HTTP/1.1 200 OK
    Date: Fri, 22 May 2009 06:07:21 GMT
    Content-Type: text/html; charset=UTF-8
    \r\n
    <body>
*/

/**
 * 一个状态响应码的枚举
 * */

/**
 * 此类用于生成http协议中的响应报文
 * 生成http响应报文的步骤包括:
 * 添加状态行, 添加头部, 添加响应报文
*/
class response
{
private:
  std::string statecode;
  std::string header;
  std::string body;

  int code_;
  bool iskeepalive_;
  std::string path_;
  std::string srcdir_;

  char* file;
  //stat数据结构存储的是文件信息，包含文件的各种属性，像是文件类型，权限，大小等
  struct stat filestat;
  
public:
  response(/* args */);
  ~response();
  void init(const std::string& srcDir, std::string path, bool isKeepAlive, int code);
  void makeresponse(buffer& buff); //生成响应报文

  void unmapfile(); //取消文件映射
  char* File(); //返回文件内容
  size_t filelen(); //返回文件长度
  std::string filetype(); //返回文件类型


private:
  void genestatecode(buffer& buff); //添加报文首行
  void addheader(buffer& buff); //添加报文头配置信息
  void addbody(buffer& buff); //添加报文数据
  void errorhtml(); //在错误code下，对响应文件stat绑定对应的错误html
  void errorcontent(buffer& buff, std::string); //在数据出错的情况下, 在报文中添加错误信息数据

private:
  static const std::unordered_map<std::string, std::string> SUFFIX_TYPE;
  static const std::unordered_map<size_t, std::string> CODE_STATUS;
  static const std::unordered_map<int, std::string> CODE_PATH;
};


#endif