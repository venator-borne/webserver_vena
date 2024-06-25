//
// Created by Venator on 2024/6/23.
//

#ifndef WEBSERVER_VENA_SERVER_CFG_H
#define WEBSERVER_VENA_SERVER_CFG_H

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

#define HTTP_VER "HTTP/1.1"
#define STATUS_LINE(CODE, STATUS) HTTP_VER CODE STATUS
//const std::string HTTP_VER = "HTTP/1.1";
//
//
//constexpr char* http_status_line(int code, std::string status) {
////    char* l;
//    std::string l = std::to_string(code) + " " + status;
////    return ;
//}

#endif //WEBSERVER_VENA_SERVER_CFG_H
