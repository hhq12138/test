/*
        使用多线程实现买票的案例
        有三个窗口，一共是100张票

*/

#include <stdio.h>
#include <pthread.h>
int tickets = 100;
void *sellticket(void *arg)
{
    // sell
    
    while (tickets > 0)
    {
        printf("%ld are selling No %d tickets", pthread_self(), tickets);
        tickets--;
    }
    return NULL;
}
int main()
{
    // create 3 pthreads
    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, sellticket, NULL);
    pthread_create(&tid2, NULL, sellticket, NULL);
    pthread_create(&tid3, NULL, sellticket, NULL);

    // recycle pthread resouce
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    // set thread detach
    pthread_detach(tid1);
    pthread_detach(tid2);
    pthread_detach(tid3);

    // exit
    pthread_exit(NULL);
    return 0;
}
