#include <iostream>
#include <memory>

using namespace std;

// shared_ptr的基础应用
void test01()
{

    shared_ptr<int> p1 = make_shared<int>();

    *p1 = 10;
    std::cout << "p1= " << (*p1) << std::endl;

    std::cout << "p1的引用次数" << p1.use_count() << std::endl;

    // 使用拷贝构造的方法，引用计数+1
    shared_ptr<int> p2(p1);
    std::cout << "p1的引用次数" << p1.use_count() << std::endl;
    std::cout << "p2的引用次数" << p2.use_count() << std::endl;

    // 比较智能指针
    if (p1 == p2)
    {
        std::cout << "p1和p2指向相同的指针" << std::endl;
    }

    // 无参数reset，即指针重置
    p1.reset();
    std::cout << "p1的引用次数" << p1.use_count() << std::endl;

    // 有参数reset，即指针重置后创建一个新的对象
    p1.reset(new int(11));
    std::cout << "p1的引用次数" << p1.use_count() << std::endl;
}

shared_ptr<string> factory(const char *p)
{
    shared_ptr<string> p1 = make_shared<string>(p);
    return p1;
}

void use_factory()
{
    shared_ptr<string> p = factory("huanghongqing");
    std::cout << p.use_count() << std::endl;
    std::cout << *p << std::endl; // p离开作用域时，p引用的对象被销毁
}

shared_ptr<string> return_shared_ptr()
{
    shared_ptr<string> p = factory("huanghongqing");
    std::cout << p.use_count() << std::endl;
    std::cout << *p << std::endl;
    return p; // 返回p时，引用计数增加，p离开了作用域，但其指向的内存不会被释放掉
}

int main(int argc, const char *argv[])
{
    // test01();
    use_factory();

    auto temp = return_shared_ptr();
    std::cout << temp.use_count() << std::endl;

    return 0;
}