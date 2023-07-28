#pragma once
#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>
using namespace std;
/**
 * 加锁的懒汉式单例实现
 */
class SingleInstance
{
private:
    // 将构造和析构成为私有，禁止外部构造和析构
    SingleInstance(/* args */);
    ~SingleInstance();
    // 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
    SingleInstance(const SingleInstance &signal);
    const SingleInstance &operator=(const SingleInstance &singnal);

    // 创建唯一单实例对象指针
    static SingleInstance *m_SingleInstance;
    // 创建互斥锁
    static std::mutex m_Mutex;

public:
    // 获取单例对象
    static SingleInstance *GetInstance();

    // 释放单实例，进程退出时调用
    static void deleteInstance();

    // 打印实例地址
    void Print();
};
