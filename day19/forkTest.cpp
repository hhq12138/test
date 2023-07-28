#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main(int argc, const char *argv[])
{
    pid_t pid;
    int i = 0;
    for (int i = 0; i < 10; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            break;
            std::cout << "child id :" << getpid() << std::endl;
            sleep(1);
        }
        else if (pid > 0)
        {
            std::cout << "parent id:" << getpid() << std::endl;
            sleep(1);
        }
    }

    return 0;
}