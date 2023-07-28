// g++ std-thread-array.cpp -o a.out -std=c++11 -pthread
#include <iostream>
#include <thread>

void foo(int n)
{
    std::cout << "foo() " << n << "\n";
}

int main()
{
    std::thread threads[3];

    for (int i = 0; i < 3; i++)
    {
        threads[i] = std::thread(foo, i);
    }

    for (int i = 0; i < 3; i++)
    {
        threads[i].join();
    }

    std::cout << "main() exit.\n";

    return 0;
}
