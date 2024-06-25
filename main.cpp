#include <iostream>
#include <vector>
#include <memory>
#include <sys/mman.h>
#include <sys/utsname.h>
#include <stdio.h>

using namespace std;

int main(int argc, char const *argv[])
{
    struct utsname buffer;

    if (uname(&buffer) != 0) {
        perror("uname");
        return 1;
    }

    printf("System Name: %s\n", buffer.sysname);
    printf("Node Name: %s\n", buffer.nodename);
    printf("Release: %s\n", buffer.release);
    printf("Version: %s\n", buffer.version);
    printf("Machine: %s\n", buffer.machine);

    return 0;
}
