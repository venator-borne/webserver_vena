#include "response.h"

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


void response::mmapfile() {
    if (file) {

    }
    mmap()
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


void response::errorhtml() {
    if (CODE_PATH.count(code_)) {
        path_ = CODE_PATH.find(code_)->second;
        stat((srcdir_ + path_).data(), &filestat);
    }
}

void response::genestatecode(buffer& buff) {
    std::string status;
    if (CODE_STATUS.count(code_)) {
        status = CODE_STATUS.find(code_)->second;
    } else {
        code_ = 400;
        status = CODE_STATUS.find(400)->second;
    }
    buff.append(HTTP_VER + " " + std::to_string(code_) + " " + status);
}

void response::addbody() {

}

void response::addheader() {

}