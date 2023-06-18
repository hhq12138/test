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

    // create a thread_attr
    pthread_attr_t attr;
    // init
    pthread_attr_init(&attr);

    // set
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_t tid;
    int ret = pthread_create(&tid, &attr, callback, NULL);

    if (ret != 0)
    {
        char *errstr = strerror(ret);
        printf("error: %s\n", errstr);
    }

    // getsize
    size_t size;
    pthread_attr_getstacksize(&attr, &size);

    printf("thread stack size = %ld\n", size);

    printf("tid:%ld,main thread id:%ld\n ", tid, pthread_self());

    //release thread resource
    pthread_attr_destroy(&attr);

    // main thread exit
    pthread_exit(NULL);

    return 0;
}
