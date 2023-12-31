#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {

        int i = 0;
        for (i = 0; i < 5; i++)
        {
            printf("child process:%d,my parent process:%d\n", getpid(), getppid());
            sleep(1);
        }
    }
    else if (pid > 0)
    {
        printf("parent process:%d\n", getpid());
        sleep(2);
        printf("kill child process now\n");
        kill(pid, SIGINT);
    }

    return 0;
}