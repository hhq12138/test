#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
void *callback(void *arg)
{
    printf("child thread id:%ld\n", pthread_self());
    sleep(3);
    return NULL;
}
int main()
{

    // create a pthread
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, callback, NULL);

    if (ret != 0)
    {
        char *errstr = strerror(ret);
        printf("error: %s\n", errstr);
    }

    // main thread
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", i);
    }

    printf("tid:%ld,main thread id:%ld\n ", tid, pthread_self());

    // main thread use pthread_join to retrieve the resource of pthread
    ret = pthread_join(tid, NULL);
    if (ret != 0)
    {
        char *errstr = strerror(ret);
        printf("error: %s\n", errstr);
    }
    printf("回收子进程资源成功！\n");
    // main thread exit
    pthread_exit(NULL);

    return 0;
}
