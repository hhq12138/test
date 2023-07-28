#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
/**
 * 只能用于具有共同祖先的进程（具有亲缘关系的进程）之间的通信
 */
#define MESSAGE "This message is from child:hello ,parent!"

int main(int argc, const char *argv[])
{

    // 定义读写文件描述符
    // pipefd[0] ---->读端
    // pipefd[1] ---->写端
    int pipefd[2];

    char buf[1024]; // 读写缓冲区

    // 保存进程的退出状态
    int status;

    // 创建管道
    if (pipe(pipefd) < 0)
    {
        perror("创建管道错误！");
        return -1;
    }
    std::cout << "创建管道成功！" << std::endl;

    // 创建进程
    pid_t pid = fork();
    if (pid == 0)
    {
        close(pipefd[0]);            // 子进程关闭读端
        memset(buf, 0, sizeof(buf)); // 初始化buf

        write(pipefd[1], MESSAGE, sizeof(MESSAGE)); // 子进程写入数据
    }
    else if (pid < 0)
    {
        perror("创建子进程错误");
        return -1;
    }
    else if (pid > 0)
    {
        close(pipefd[1]);                           // 父进程关闭写端
        int rv = read(pipefd[0], buf, sizeof(buf)); // 父进程读数据
        if (rv < 0)
        {

            perror("父进程读取管道数据失败！");
            return -1;
        }
        std::cout << "父进程从管道读取到" << rv << "字节，内容为：" << buf << std::endl;
    }
    waitpid(pid, &status, 0);
    return 0;
}