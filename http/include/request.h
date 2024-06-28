#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <regex>
#include <unordered_map>

class request
{
public:
  enum PARSE_STATE {
    REQUEST_LINE,
    HEADERS,
    BODY,
    FINISH,
  };

private:
  PARSE_STATE state_;
  std::string method_, path_, version_, body_;
  std::unordered_map<std::string, std::string> header_;
  std::unordered_map<std::string, std::string> post_;

  
public:
  request(/* args */);
  ~request();

  void init();
  void parse();
private:
  void parsereqline(); //解析请求行
  void parsereqheader(); //解析请求头
  void parsereqbody(); //解析请求体


};

#endif