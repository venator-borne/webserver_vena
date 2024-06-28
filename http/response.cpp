#include "./include/response.h"

response::response() {
    code_ = -1;
    path_ = srcdir_ = "";
    iskeepalive_ = false;
    file = nullptr;
    filestat = { 0 };
}

void response::init(const std::string& srcDir, std::string path, bool isKeepAlive, int code) {
    assert(srcDir != "");
    if(file) {
        unmapfile();
    }
    code_ = code;
    iskeepalive_ = isKeepAlive;
    path_ = path;
    srcdir_ = srcDir;
    file = nullptr;
    filestat = {0};
}


void response::makeresponse(buffer& buff) {
    //获取请求的文件信息
    if(stat((srcdir_ + path_).data(), &filestat) < 0 || S_ISDIR(filestat.st_mode)) {
        code_ = 404;
    } else if (!(filestat.st_mode & S_IROTH)) {
        //其他用户是否有读权限
        code_ = 403;
    } else if (code_ == -1) {
        code_ = 200;
    }

    errorhtml();
    genestatecode(buff);
    addheader(buff);
    addbody(buff);
}

void response::unmapfile() {
    if(file) {
        munmap(file, filestat.st_size);
        file = nullptr;
    }
}

char *response::File() {
    return file;
}

size_t response::filelen() {
    return filestat.st_size;
}

std::string response::filetype() {
  size_t pos = path_.find_last_of(".");
  if (pos == std::string::npos) return "text/plain";

  std::string type = path_.substr(pos);
  if (SUFFIX_TYPE.count(type)) {
    return SUFFIX_TYPE.find(type)->second;
  }
  return "text/plain";
}


void response::errorhtml() {
    if (CODE_PATH.count(code_)) {
        path_ = CODE_PATH.find(code_)->second;
        stat((srcdir_ + path_).data(), &filestat);
    }
}

void response::errorcontent(buffer& buff, std::string msg) {
  std::string body;
  std::string status;
  body += "<html><title>Error</title>";
  body += "<body bgcolor=\"ffffff\">";
  if(CODE_STATUS.count(code_) == 1) {
      status = CODE_STATUS.find(code_)->second;
  } else {
      status = "Bad Request";
  }
  body += std::to_string(code_) + " : " + status  + "\n";
  body += "<p>" + msg + "</p>";
  body += "<hr><em>WebServer</em></body></html>";
  buff.append("Content-length: " + std::to_string(body.size()) + "\r\n\r\n");
  buff.append(body);
}

void response::genestatecode(buffer& buff) {
    std::string status;
    if (CODE_STATUS.count(code_)) {
        status = CODE_STATUS.find(code_)->second;
    } else {
        code_ = 400;
        status = CODE_STATUS.find(400)->second;
    }
    buff.append(STATUS_LINE(code_, status));
}

void response::addheader(buffer& buff) {
  buff.append(CONNECTION);
  if (iskeepalive_) {
    buff.append(KEEP_ALIVE);
    buff.append(KEEP_ALIVE_CFG(6, 120));
  } else {
    buff.append(CLOSE);
  }

  buff.append(CONTENT_TYPE(filetype()));
}

//
void response::addbody(buffer& buff) {
  //data()返回的是const char*类型
  int fd = open((srcdir_ + path_).data(), O_RDONLY);
  if (fd < 0) {
    errorcontent(buff, "File NOT FOUND!");
    return;
  }

  //做内存映射
  int *mapf = (int*)mmap(0, filestat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (*mapf == -1) {
    errorcontent(buff, "File NOT FOUND!");
    return;
  }
  file = (char*)mapf;
  std::string str(file);
  close(fd);
  buff.append("Content-length: " + std::to_string(filestat.st_size) + "\r\n\r\n");
  buff.append(str);
}

