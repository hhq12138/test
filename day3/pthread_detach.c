#include <stdio.h>
#include <pthread.h>
#include <string.h>

void *callback(void *arg)
{
    printf("child thread...\n");
    printf("arg=%d\n",*(int *)arg);
    return NULL;
    
}
int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, callback, NULL);

    if (ret != 0)
    {
        char *errstr = strerror(ret);
        printf("error:%s\n", errstr);
    }
    printf("tid:%ld,main thread id:%ld\n ", tid, pthread_self());

    pthread_detach(tid);
    pthread_exit(NULL);
    return 0;
    
}
