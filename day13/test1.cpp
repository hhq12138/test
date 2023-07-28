#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
    int num = 3;
    int *pNum1 = &num;
    *pNum1 = 20;
    int *pNum2 = pNum1;
    num *= 2;
    std::cout << *pNum2 << std::endl;
    return 0;
}