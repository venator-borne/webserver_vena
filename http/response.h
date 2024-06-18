// 将该内存映射的指针加入buff，至此，报文的所有内容就都在buff中”，这句话说的并不对，mmap映射文件的指针没有加入buff，只是httpconn中处理请求的函数将ivo[1]的指针指向了这个文件
#ifndef RESPONSE_H
#define RESPONSE_H
#include <iostream>
#include <string>
#include <unordered_map>
/**
 * http报文格式
 *  HTTP/1.1 200 OK
    Date: Fri, 22 May 2009 06:07:21 GMT
    Content-Type: text/html; charset=UTF-8
    \r\n
    <body>
*/

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
  
public:
  response(/* args */);
  ~response();

  enum class CODE : size_t;
private:
  void genestatecode();
  void addheader();
  void addbody();

private:
  static const std::unordered_map<std::string, std::string> SUFFIX_TYPE;
  static const std::unordered_map<size_t, std::string> CODE_STATUS;
  CODE code;
};


#endif