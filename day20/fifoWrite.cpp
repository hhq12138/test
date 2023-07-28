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
 * 可以实现两个毫不相关进程之间的通信
 */
int main(int argc, const char *argv[])
{
    // 判断文件是否存在
    int ret = access("test", F_OK);
    if (ret < 0)
    {
        std::cout << "管道不存在，创建管道" << std::endl;
        ret = mkfifo("test", 0664);
        if (ret < 0)
        {
            perror("mkfifo");
            exit(0);
        }
    }

    // 以只写的方式打开管道
    int fd = open("test", O_WRONLY);
    if (fd == -1)
    {
        perror("open");
        exit(0);
    }
    // 写数据
    for (int i = 0; i < 100; i++)
    {
        char buf[1024];
        sprintf(buf, "hello,%d\n", i);
        printf("write data:%s\n", buf);
        write(fd, buf, strlen(buf));
        sleep(1);
    }
    close(fd);

    return 0;
}