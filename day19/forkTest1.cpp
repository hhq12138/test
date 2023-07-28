#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main(int argc, const char *argv[])
{

    int num = 10;
    pid_t pid = fork();
    // 子进程
    if (pid == 0)
    {
        num = 20;
        std::cout << "child process num：" << num << std::endl;
        std::cout << "child process num address:" << &num << std::endl;
    }
    // 父进程
    else if (pid > 0)
    {
        std::cout << "parent process num：" << num << std::endl;
        std::cout << "parent process num address:" << &num << std::endl;
    }
    return 0;
}