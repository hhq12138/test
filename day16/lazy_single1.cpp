#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <string>
/**
 * 使用智能指针shard_ptr
 */
class Singleton
{

public:
    // 获取实例对象，返回shared_ptr
    static std::shared_ptr<Singleton> getSingleton();

    void print()
    {
        std::cout << "Hello World." << std::endl;
    }
    // __PRETTY_FUNCTION__:用来返回函数的详细信息
    ~Singleton()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

private:
    Singleton()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

static std::shared_ptr<Singleton> singleton = nullptr;
static std::mutex singletonMutex;

std::shared_ptr<Singleton> Singleton::getSingleton()
{
    if (singleton == nullptr)
    {
        std::unique_lock<std::mutex> lock(singletonMutex);
        if (singleton == nullptr)
        {
            auto temp = std::shared_ptr<Singleton>(new Singleton());
            singleton = temp;
        }
    }
    return singleton;
}

void Print()
{
    auto single = Singleton::getSingleton();
    singletonMutex.lock();
    std::cout << single << std::endl;
    singletonMutex.unlock();
}

int main(int argc, const char *argv[])
{
    // auto single1 = Singleton::getSingleton();
    // std::cout << &single1 << std::endl;
    // auto single2 = Singleton::getSingleton();
    // std::cout << &single2 << std::endl;

    thread threads[10];

    // 创建10个线程
    for (auto &t : threads)
        t = thread(Print);
    // 对每个线程调用join，主线程等待子线程完成运行
    for (auto &t : threads)
        t.join();

    return 0;
}
