#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
// 编写一个程序，把常规信号（1-31）未决状态打印到屏幕
int main()
{

    // 设置2、3号信号阻塞
    sigset_t set;
    sigemptyset(&set);

    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    sigprocmask(SIG_BLOCK, &set, NULL);
    while (1)
    {
        // 获取当前未决信号集的数据
        sigset_t pendingset;
        sigemptyset(&pendingset);
        sigpending(&pendingset);

        // 遍历前32位
        for (int i = 1; i <= 31; i++)
        {
            if (sigismember(&pendingset, i) == 1)
            {
                printf("1");
            }
            else if (sigismember(&pendingset, i) == 0)
            {
                printf("0");
            }
            else
            {
                perror("sigismember");
            }
        }

        printf("\n");
    }

    return 0;
}