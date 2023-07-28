#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>
void myFun(int num)
{
    printf("捕捉到的信号：%d\n", num);
    // 回收子进程PCB的资源
    wait(NULL);
}
int main()
{
    // 创建一些子进程
    pid_t pid;
    for (int i = 0; i < 20; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            break;
        }
    }
    if (pid > 0)
    {
        // 父进程
        // 捕捉子进程死亡时发送的SIGCHILD信号

        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = myFun;
        sigemptyset(&act.sa_mask);
        sigaction(SIGCHLD, &act, NULL);
        while (1)
        {
            printf("parent process pid :%d\n", getpid());
            sleep(2);
        }
    }
    else if (pid == 0)
    {
        // 子进程
        printf("child process pid:%d\n", getpid());
    }

    return 0;
}
