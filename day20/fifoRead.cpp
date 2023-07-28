#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
using namespace std;
/**
 * 命名管道由mkfifo函数创建，由open函数打开
 */
int main(int argc, const char *argv[])
{
    //     // 判断文件是否存在
    //     int ret = access("test", F_OK);
    //     if (ret < 0)
    //     {
    //         std::cout << "管道不存在，创建管道" << std::endl;
    //         ret = mkfifo("test", 0664);
    //         if (ret < 0)
    //         {
    //             perror("mkfifo");
    //             exit(0);
    //         }
    //     }

    // 以只读的方式打开管道
    int fd = open("test", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(0);
    }
    // 读数据
    while (1)
    {
        char buf[1024] = {0};
        int len = read(fd, buf, sizeof(buf));
        if (len == 0)
        {
            std::cout << "写端断开了连接" << std::endl;
            break;
        }
        std::cout << "recv data:" << buf << std::endl;
    }

    close(fd);

    return 0;
}