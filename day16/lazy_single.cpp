#include "lazy_single.h"

SingleInstance *SingleInstance::m_SingleInstance = nullptr;
std::mutex SingleInstance::m_Mutex;

SingleInstance::SingleInstance(/* args */)
{
    std::cout << "构造函数" << std::endl;
}

SingleInstance::~SingleInstance()
{

    std::cout << "析构函数" << std::endl;
}

const SingleInstance &SingleInstance::operator=(const SingleInstance &singnal)
{
    // TODO: 在此处插入 return 语句
}

SingleInstance *SingleInstance::GetInstance()
{
    // 判断指针是否为空，即对象是否首次被创建
    // std::unique_lock<mutex> lock(m_Mutex); // 加锁
    if (m_SingleInstance == nullptr)
    {
        std::cout << "1111" << std::endl;

        // 第二个if判断，防止线程冲突，称为双检锁
        if (m_SingleInstance == nullptr)

        {
            sleep(1);
            std::cout << "3333" << std::endl;
            // 与标准new的区别是，new在分配内存失败时会抛出异常，
            // 而"new(std::nothrow)"在分配内存失败时会返回一个空指针。
            SingleInstance *temp = new (nothrow) SingleInstance();
            m_SingleInstance = temp;

            std::cout << m_SingleInstance << std::endl;
        }
    }
    // std::unique_lock<mutex> unlock(m_Mutex); // 解锁
    std::cout << "2222" << std::endl;
    return m_SingleInstance;
}

void SingleInstance::deleteInstance()
{
    unique_lock<mutex> lock(m_Mutex); // 加锁
    if (m_SingleInstance)
    {
        delete m_SingleInstance;
        m_SingleInstance = nullptr;
    }
}

void SingleInstance::Print()
{

    SingleInstance *singleton = SingleInstance::GetInstance();
    m_Mutex.lock();
    std::cout << singleton << std::endl;
    m_Mutex.unlock();
}

void print_address()
{
}

// 测试案例1：创建两个实例对象，看它们的地址是否相同
void test1()
{
    SingleInstance *single1 = SingleInstance::GetInstance();
    single1->Print();
    // std::cout << single1 << std::endl;
    // single1->deleteInstance();
    SingleInstance *single2 = SingleInstance::GetInstance();
    // std::cout << single2 << std::endl;
    single2->Print();
}

// 测试案例2：创建一组线程，观察是否会导致线程冲突
void test2()
{
    thread threads[10];

    // 创建10个线程
    for (auto &t : threads)
        t = thread(SingleInstance::Print);
    // 对每个线程调用join，主线程等待子线程完成运行
    for (auto &t : threads)
        t.join();
}
int main(int argc, const char *argv[])
{
    test2();

    return 0;
}