#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct sockInfo{
    int fd;
    pthread_t tid;
    struct sockaddr_in addr;
};

void *working(void *arg){

    //子线程和客户端通信

    return NULL;
}
int main() {

    
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

    /*
        循环等待客户端连接，一旦一个客户端连接进来，就创建一个子线程进行通信
    */
   while (1)
   {
        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);
        // accept connection
        int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);


        struct sockInfo * pinfo;
        

        // create pthread
        pthread_t tid;
        pthread_create(&tid,NULL,working,NULL);

   }
   

    return 0;
}
