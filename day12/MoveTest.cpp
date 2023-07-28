#include <iostream>

using namespace std;
class Person
{
private:
    int *m_age;

public:
    // 有参构造
    Person(int age) : m_age(new int(age))
    {
        std::cout << "Person(int age)有参" << std::endl;
    }
    // 拷贝构造
    Person(const Person &p) : m_age(new int(*p.m_age))
    {
        std::cout << "Person(const Person& p)拷贝" << std::endl;
    }
    // 移动构造
    Person(Person &&p) : m_age(p.m_age)
    {
        p.m_age = nullptr;
        std::cout << "Person(Person &&p) 移动" << std::endl;
    }
    // 析构构造
    ~Person()
    {
        std::cout << "~Person() 析构" << std::endl;
        delete m_age;
    }

    int getAge(void)
    {
        return *m_age;
    }
};

Person getNum()
{
    Person a(100);
    return a;
}

int main(int argc, const char *argv[])
{
    Person temp = getNum();
    Person a(temp);
    cout << "a=" << a.getAge() << endl;
    cout << "-----------------" << endl;
    Person temp(1000);
    Person b(temp);
    cout << "b=" << b.getAge() << endl;
    cout << "-----------------" << endl;

    return 0;
}