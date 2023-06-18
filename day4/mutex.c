#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int tickets = 100;
// create a mutex
pthread_mutex_t mutex;
void *sellticket(void *arg)
{

    // sell
    while (1)
    {
        // lock
        pthread_mutex_lock(&mutex);
        if (tickets > 0)
        {
            printf("%ld are selling No %d tickets", pthread_self(), tickets);
            tickets--;
        }
        else
        {
            // deblocking
            pthread_mutex_unlock(&mutex);
            break;
        }
        // deblocking
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}
int main()
{
    // init mutex
    pthread_mutex_init(&mutex, NULL);

    // create 3 pthreads
    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, sellticket, NULL);
    pthread_create(&tid2, NULL, sellticket, NULL);
    pthread_create(&tid3, NULL, sellticket, NULL);

    // recycle pthread resouce
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    // exit
    pthread_exit(NULL);

    // release mutex resource
    pthread_mutex_destroy(&mutex);
    return 0;
}
