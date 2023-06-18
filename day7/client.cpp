#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket error");
        exit(-1);
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.1.3", &server_addr.sin_addr.s_addr);
    server_addr.sin_port = htons(1234);

    int ret = connect(fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret < 0)
    {
        perror("connect error");
        exit(-1);
    }

    // 数据通信
    char buf[1024];
    while (1)
    {
        int len = recv(fd, &buf, sizeof(buf), 0);

        if (len == -1)

        {
            perror("read");
            exit(-1);
        }
        else if (len > 0)
        {
            printf("recv sever data: %s\n", buf);
        }
        else if (len == 0)
        {
            printf("server closed...");
            break;
        }
    }
    close(fd);
    return 0;
}