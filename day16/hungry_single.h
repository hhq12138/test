#include <iostream>
using namespace std;

/**
 * 实现饿汉式单例
 */

class Singleton
{
private:
    // 禁止外部构造
    Singleton(/* args */);

    // 禁止外部析构
    ~Singleton();

    // 禁止外部拷贝
    Singleton(const Singleton &single);

    // 禁止外部赋值操作
    const Singleton &operator=(const Singleton &single);

public:
    // 获取单实例对象
    static Singleton GetInstance();

    // 打印实例地址
    void Print();
};
