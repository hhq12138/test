#include <iostream>
#include <string>
using namespace std;

// 算法类
class Operation
{

public:
    virtual ~Operation()
    {
    }
    virtual int GetResult(int num1, int num2)
    {
        return 0;
    }
};

// 加法类
class operationAdd : public Operation
{

public:
    int GetResult(int num1, int num2)
    {
        return num1 + num2;
    }
};

// 减法类
class operationSub : public Operation
{

public:
    int GetResult(int num1, int num2)
    {
        return num1 - num2;
    }
};

// 乘法类
class operationMul : public Operation
{

public:
    int GetResult(int num1, int num2)
    {
        return num1 * num2;
    }
};

// 除法类
class operationDiv : public Operation
{

public:
    int GetResult(int num1, int num2)
    {
        return num1 / num2;
    }
};

// 创建一个简单工厂类
class OperationFactory
{
public:
    OperationFactory()
    {
    }
    Operation *createOperate(char operate)
    {
        // Operation *oper = nullptr;
        // while (true)
        // {

        switch (operate)
        {
        case '+':

            return new operationAdd();
            break;
        case '-':
            return new operationSub();
            break;
        case '*':
            return new operationMul();
            break;
        case '/':
            return new operationAdd();
            break;

        default:
            return NULL;
            break;
        }

        // }
    }
};

int main(int argc, const char *argv[])
{
    Operation oper;
    OperationFactory of;
    oper = *(of.createOperate('+'));
    int result = oper.GetResult(1, 2);
    std::cout << result << std::endl;
    return 0;
}