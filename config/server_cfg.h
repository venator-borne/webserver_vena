//
// Created by Venator on 2024/6/23.
//

#ifndef WEBSERVER_VENA_SERVER_CFG_H
#define WEBSERVER_VENA_SERVER_CFG_H

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BORDER "\r\n"

#define HTTP_VER "HTTP/1.1"
#define STATUS_LINE(CODE, STATUS) HTTP_VER " " #CODE " " #STATUS BORDER

#define CONNECTION "Connection: "
#define KEEP_ALIVE "keep-alive"BORDER
#define KEEP_ALIVE_CFG(MAX, TIMEOUT) "keep-alive: max="#MAX", timeout="#TIMEOUT BORDER
#define CLOSE "close"BORDER

#define CONTENT_TYPE(TYPE) "Content-type: "#TYPE BORDER

#define MSG(M) "<html><title>Error</title>" \
  "<body bgcolor=\"ffffff\">" \
  "Err: Cannot find data!\n" \
  "<p>"#M"</p>" \
  "<hr><em>TinyWebServer</em></body></html>"
  
  #endif //WEBSERVER_VENA_SERVER_CFG_H
