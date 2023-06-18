#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
void recyleChild(int arg)
{
    while (1)
    {
        int ret = waitpid(-1, NULL, WNOHANG);
        if (ret == -1)
        {
            break;
        }
        else if (ret == 0)
        {
            break;
        }
        else if (ret > 0)
        {
            printf("child process %d has been recyled", ret);
        }
    }
}
int main()
{
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = recyleChild;
    // catch signal
    sigaction(SIGCHLD, &act, NULL);
    // create socket
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    if (lfd == -1)
    {
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = INADDR_ANY;
    // bind
    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret == -1)
    {
        perror("bind");
        exit(-1);
    }
    // listen
    ret = listen(lfd, 5);
    if (ret == -1)
    {
        perror("listen");
        exit(-1);
    }

    // continuous waiting for client connection in a loop
    while (1)
    {
        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);
        // accept connection
        int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);
        if (cfd == -1)
        {
            if (errno = EINTR)
            {
                continue;
            }
            perror("accpet");
            exit(-1);
        }

        // for each connection,create a child process to communicate with the client
        pid_t pid = fork();
        if (pid == 0)
        {
            // child process
            // achieve information of client
            char cliIp[16];
            inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, cliIp, sizeof(cliIp));
            unsigned short cliPort = ntohs(cliaddr.sin_port);

            printf("client ip is:%s,port is :%d\n", cliIp, cliPort);

            // accept data from client
            char recvBuf[1024] = {0};
            while (1)
            {
                int len = read(cfd, &recvBuf, sizeof(recvBuf));
                if (len == -1)
                {
                    perror("read");
                    exit(-1);
                }
                else if (len > 0)
                {
                    printf("recv client data: %s\n", recvBuf);
                }
                else
                {
                    printf("client closed...");
                    break;
                }

                write(cfd, recvBuf, strlen(recvBuf));
            }
            close(cfd);
            exit(0);
        }
    }
    close(lfd);

    return 0;
}
