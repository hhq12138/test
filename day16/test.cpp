#include <iostream>
#include <stdexcept>
#include <thread>
#include <mutex>

#ifdef WIN32
#include <windows.h>
#define SLEEP(x) Sleep(x)
#else
#include <unistd.h>
#define SLEEP(x) usleep(x * 1000)
#endif

using namespace std;

// 懒汉式单例
class Singleton
{
private:
    static Singleton *singleton;
    Singleton() = default;
    Singleton(const Singleton &s) = default;
    Singleton &operator=(const Singleton &s) = default;

public:
    static Singleton *getInstance()
    {
        if (Singleton::singleton == nullptr)
        {
            SLEEP(10); // 休眠，模拟创建实例的时间
            singleton = new Singleton();
        }
        return singleton;
    }
};

// 必须在类外初始化
Singleton *Singleton::singleton = nullptr;
// 定义一个互斥锁
mutex m;

void print_address()
{
    // 获取实例
    Singleton *singleton1 = Singleton::getInstance();
    // 打印singleton1地址
    m.lock(); // 锁住，保证只有一个线程在打印地址
    cout << singleton1 << endl;
    m.unlock(); // 解锁
}

int main()
{
    thread threads[10];

    // 创建10个线程
    // for (auto &t : threads)
    //     thread t(print_address);

    for (int i = 0; i < 10; i++)
    {
        threads[i] = thread(print_address, i);
    }

    // t = thread(print_address);
    // 对每个线程调用join，主线程等待子线程完成运行
    for (auto &t : threads)
        t.join();
}
