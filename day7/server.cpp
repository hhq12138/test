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
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    if (lfd < 0)
    {
        perror("socket error");
        exit(-1);
    }

    struct sockaddr_in addr;
    memset(&addr, '0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(1234);

    int ret = 0;
    int flag = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    ret = bind(lfd, (struct sockaddr *)&addr, sizeof(addr));
    assert(ret >= 0);

    listen(lfd, 5);
    int cfd;
    while (1)
    {
        struct sockaddr_in cliaddr;
        socklen_t len = sizeof(cliaddr);
        cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);
        assert(cfd >= 0);
    }

    int n, i = 0;
    char buf[1024] = {0};
    while (1)
    {
        n = read(lfd, buf, sizeof(buf));
        if (n == 0) // 有客户端断开连接
        {
            printf("有客户端断开连接\n");
        }
        if (n < 0)
        {
            printf("aaaaaaaa\n");
        }
        // inet_ntop(AF_INET,&clientAddr.sin_addr,str,sizeof(str));
        // ntohs(clientAddr.sin_port);
        printf("已收到第%d次数据:%s\n", i++, buf);
        // sleep(2);
        write(lfd, buf, n);
    }

    close(cfd);
    close(lfd);

    return 0;
}