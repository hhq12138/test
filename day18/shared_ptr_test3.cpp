#include <iostream>
#include <list>
#include <memory>

using namespace std;

// 普通拷贝案例
void copyCase()
{

    list<string> v1 = {"1", "h", "q"};
    list<string> v2 = v1; // 拷贝

    v1.push_back("nb");

    for (auto p : v1)
    {
        std::cout << p << std::endl;
    }
    cout << "--------void copyCase()---------" << endl;
    for (auto &p : v2)
    {
        cout << p << endl;
    }
} // v1和v2属于不同的对象，一个改变不会影响另一个状态

// shared_ptr拷贝案例
void sharedCase()
{
    shared_ptr<list<string>> v1 = make_shared<list<string>>(2, "bb");
    shared_ptr<list<string>> v2 = v1;
    (*v1).push_back("yyds");

    for (auto p : *v1)
    {
        std::cout << p << std::endl;
    }

    cout << "--------void sharedCase()---------" << endl;
    for (auto p : *v2)
    {
        cout << p << endl;
    }
    std::cout << v2.use_count() << std::endl;
} // v1和v2属于同一个对象的两个引用，有引用计数为证，其内容的改变是统一的

int main(int argc, const char *argv[])
{

    // copyCase();

    sharedCase();

    return 0;
}