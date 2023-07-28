#include "hungry_single.h"

const Singleton &Singleton::operator=(const Singleton &single)
{
    // TODO: 在此处插入 return 语句
}

Singleton Singleton::GetInstance()
{
    static Singleton single;
    return single;
}

void Singleton::Print()
{
    std::cout << "我的实例内存地址是:" << this << std::endl;
}

Singleton::Singleton(/* args */)
{
    std::cout << "构造函数" << std::endl;
}

Singleton::~Singleton()
{
    std::cout << "析构函数" << std::endl;
}

// 测试案例：创建两个实例对象，看它们的地址是否相同
void test1()
{

    auto single1 = Singleton::GetInstance();
    std::cout << &single1 << std::endl;
    // single1->deleteInstance();
    auto single2 = Singleton::GetInstance();
    std::cout << &single2 << std::endl;
}

int main(int argc, const char *argv[])
{
    test1();

    return 0;
}
