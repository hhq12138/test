#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main()
{

    int seconds = alarm(10);
    printf("seconds = %d\n", seconds);

    sleep(2);
    seconds = alarm(2);
    printf("seconds = %d\n", seconds);

    while (1)
    {
        /* code */
    }
    return 0;
}