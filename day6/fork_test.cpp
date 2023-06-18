#include <stdio.h>
#include <iostream>
#include <unistd.h>

int main()
{

    std::cout << "pid=" << getpid() << std::endl;
    return 0;
}