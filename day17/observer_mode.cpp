#include <iostream>
#include <list>
#include <memory>
#include <algorithm>
// 万能头文件
// #include <bits/stdc++.h>

using namespace std;

//
// 观察者模式
//

class Observer;
// 抽象被观察者
class Subject
{
public:
    // 初始化被观察者的状态为0
    Subject() : m_nState(0) {}

    virtual ~Subject() = default;

    // 注册观察者
    virtual void Attach(const shared_ptr<Observer> pObserver) = 0;

    // 注销观察者
    virtual void Detach(const shared_ptr<Observer> pObserver) = 0;

    // 通知观察者
    virtual void Notify() = 0;

    // 获取被观察者的状态
    virtual int GetState() { return m_nState; }

    void SetState(int state)
    {
        std::cout << "Subject updated !" << std::endl;
        m_nState = state;
    }

protected:
    // 存放观察者的容器
    list<shared_ptr<Observer>> m_pObserver_list;

    // 被观察者状态
    int m_nState;
};

// 抽象观察者
class Observer
{
public:
    virtual ~Observer() = default;

    Observer(const shared_ptr<Subject> pSubject, const string &name = "unknown")
        : m_pSubject(pSubject), m_strName(name) {}

    virtual void Update() = 0;

    virtual const string &name() { return m_strName; }

protected:
    // 存放被观察者的指针
    shared_ptr<Subject> m_pSubject;

    // 观察者姓名
    string m_strName;
};

// 具体被观察者
class ConcreteSubject : public Subject
{
public:
    void Attach(const shared_ptr<Observer> pObserver) override
    {
        // 如果该观察者在list中不存在，则注册该观察者
        auto it = find(m_pObserver_list.begin(), m_pObserver_list.end(), pObserver);
        if (it == m_pObserver_list.end())
        {
            std::cout << "Attach observer" << pObserver->name() << std::endl;
            m_pObserver_list.emplace_back(pObserver);
        }
    }
    void Detach(const shared_ptr<Observer> pObserver) override
    {
        std::cout << "Detach observer" << pObserver->name() << std::endl;
        m_pObserver_list.remove(pObserver);
    }

    // 循环通知所有的观察者
    void Notify() override
    {
        auto it = m_pObserver_list.begin();
        while (it != m_pObserver_list.end())
        {
            (*it++)->Update();
        }
    }
};

// 具体观察者1
class Observer1 : public Observer
{
public:
    Observer1(const shared_ptr<Subject> pSubject, const string &name = "unknown")
        : Observer(pSubject, name)
    {
    }

    void Update() override
    {
        std::cout << "Observer1_" << m_strName << "get the update.new state is:" << m_pSubject->GetState() << std::endl;
    }
};

// 具体观察者2
class Observer2 : public Observer
{
public:
    Observer2(const shared_ptr<Subject> pSubject, const string &name = "unknown")
        : Observer(pSubject, name)
    {
    }

    void Update() override
    {
        std::cout << "Observer2_" << m_strName << "get the update.new state is:" << m_pSubject->GetState() << std::endl;
    }
};

int main(int argc, const char *argv[])
{
    // 创建被观察者
    shared_ptr<Subject> pSubject = make_shared<ConcreteSubject>();

    // 创建观察者
    shared_ptr<Observer> pObserver1_1 = make_shared<Observer1>(pSubject, "1");
    shared_ptr<Observer> pObserver1_2 = make_shared<Observer1>(pSubject, "2");
    shared_ptr<Observer> pObserver1_3 = make_shared<Observer1>(pSubject, "3");

    shared_ptr<Observer> pObserver2_4 = make_shared<Observer2>(pSubject, "4");
    shared_ptr<Observer> pObserver2_5 = make_shared<Observer2>(pSubject, "5");
    shared_ptr<Observer> pObserver2_6 = make_shared<Observer2>(pSubject, "6");

    // 注册观察者
    pSubject->Attach(pObserver1_1);
    pSubject->Attach(pObserver1_2);
    pSubject->Attach(pObserver1_3);
    pSubject->Attach(pObserver2_4);
    pSubject->Attach(pObserver2_5);
    pSubject->Attach(pObserver2_6);

    pSubject->SetState(2); // 改变状态
    pSubject->Notify();

    std::cout << std::string(50, '-') << std::endl;

    // 注销观察者
    pSubject->Detach(pObserver1_1);
    pSubject->Detach(pObserver1_2);

    pSubject->SetState(3);
    pSubject->Notify();

    return 0;
}