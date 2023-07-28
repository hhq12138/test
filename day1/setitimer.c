#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

/*
int setitimer(int which, const struct itimerval *restrict value,struct itimerval *restrict ovalue);
周期性地进行定时
*/

int main()
{

    struct itimerval new_value;

    new_value.it_interval.tv_sec = 2;  // 设置间隔时间
    new_value.it_interval.tv_usec = 0; // 设置间隔时间

    // 设置延迟时间
    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL, &new_value, NULL);

    if (ret == -1)
    {
        perror("setitimer");
        exit(0);
    }
    getchar();

    return 0;
}