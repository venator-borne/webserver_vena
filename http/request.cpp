#include "./include/request.h"

request::request(/* args */)
{
}

request::~request()
{
}

void request::init() {
  method_ = path_ = version_ = body_ = "";
  state_ = REQUEST_LINE;
  header_.clear();
  post_.clear();
}