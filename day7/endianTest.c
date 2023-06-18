#include <stdio.h>
#include <arpa/inet.h>

// 先定义一个联合体
union
{
    int number;
    char c;
} test;

// 为什么用这个联合体可以测试呢?
/*
    联合体:所有变量共用一块内存
        按最大的成员变量进行申请内存
        每一时刻只能有一个成员

    对于test：
        siezof(test) = 4
        如果用 c  = 1 type   ==> 每次都能够取到最低位置
*/

int main(void)
{

    test.number = 0x12345678;
    if (test.c == 0x12) // 高位存储在内存的低地址上
    {
        printf("本机为大端字节序\n");
    }
    else
    {
        printf("本机为小端字节序\n");
        
    }

    return 0;
}