#include "response.h"

enum CODE : size_t
{
  Continue = 100,
  Switching_Protocols = 101,
  OK = 200,
  Created = 201,
  No_Content = 204,
  Moved_Permanently = 301,
  Found = 302,
  Not_Modified = 304,
  Bad_Request = 400,
  Forbidden = 403,
  Not_Found = 404,
  Internal_Server_Error = 500,
  Bad_Gateway = 502,
  Service_Unavailable = 503,
} code;

const std::unordered_map<std::string, std::string> response::SUFFIX_TYPE = {
    {".html", "text/html"},
    {".xml", "text/xml"},
    {".xhtml", "application/xhtml+xml"},
    {".txt", "text/plain"},
    {".rtf", "application/rtf"},
    {".pdf", "application/pdf"},
    {".word", "application/nsword"},
    {".png", "image/png"},
    {".gif", "image/gif"},
    {".jpg", "image/jpeg"},
    {".jpeg", "image/jpeg"},
    {".au", "audio/basic"},
    {".mpeg", "video/mpeg"},
    {".mpg", "video/mpeg"},
    {".avi", "video/x-msvideo"},
    {".gz", "application/x-gzip"},
    {".tar", "application/x-tar"},
    {".css", "text/css "},
    {".js", "text/javascript "},
};

const std::unordered_map<size_t, std::string> response::CODE_STATUS = {
    {200, "OK"},
    {400, "Bad Request"},
    {403, "Forbidden"},
    {404, "Not Found"},
};

const std::unordered_map<int, std::string> response::CODE_PATH = {
    { 400, "/400.html" },
    { 403, "/403.html" },
    { 404, "/404.html" },
};