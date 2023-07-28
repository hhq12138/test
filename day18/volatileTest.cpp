#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <list>
using namespace std;

volatile std::atomic_bool isReady = false;
volatile std::atomic_int myCount = 0; // 使用原子类型
int normalCount = 0;                  // 普通全局变量，不使用原子类型
void task()
{
    while (!isReady)
    {
        std::this_thread::yield(); // 线程出让当前的CPU时间片，等待下一次调度
    }

    for (int i = 0; i < 100; ++i)
    {
        myCount++;
        normalCount++;
    }
}

int main()
{
    list<std::thread> tlist;
    for (int i = 0; i < 10; ++i)
    {
        tlist.push_back(std::thread(task));
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));
    isReady = true;

    for (std::thread &t : tlist)
    {
        t.join();
    }
    cout << "myCount:" << myCount << endl;
    cout << "normalCount:" << normalCount << endl;

    system("pause");
    return 0;
}