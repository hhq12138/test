#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{

    // create socket
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket");
        exit(-1);
    }

    // connect client
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.1.3", &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(9999);
    int ret = connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    if (ret == -1)
    {
        perror("connect");
        exit(-1);
    }

    // communication
    char recvBuf[1024] = {0};
    int i = 0;
    while (1)
    {
        sprintf(recvBuf, "data:%d\n", i++);
        write(fd, recvBuf, strlen(recvBuf));
        sleep(1);
        int len = read(fd, recvBuf, sizeof(recvBuf));
        if (len == -1)
        {
            perror("read");
            exit(-1);
        }
        else if (len > 0)
        {
            printf("recv sever data: %s\n", recvBuf);
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
