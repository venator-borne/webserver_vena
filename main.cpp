#include <iostream>
#include <vector>
#include <memory>
#include <sys/mman.h>
#include <sys/utsname.h>
#include <stdio.h>

using namespace std;

#define HTTP_VER "HTTP/1.1"
#define STATUS_LINE(CODE, STATUS) HTTP_VER " " #CODE " " STATUS
#define MSG(M) #M
int main(int argc, char const *argv[])
{
    cout << "<p>" MSG("你好") "</p>" << endl;

    return 0;
}
