#include <iostream>
#include <list>
#include <memory>
using namespace std;
/**
 * shared_ptr类保证只要有任何shared_ptr对象引用它，他就不会被释放掉。
 * 因此：不用的shared_ptr要及时erase掉节省内存
 */
int main(int argc, const char *argv[])
{
    list<shared_ptr<string>> pstrList;
    pstrList.emplace_back(make_shared<string>("1111"));
    pstrList.emplace_back(make_shared<string>("2222"));
    pstrList.emplace_back(make_shared<string>("3333"));

    for (auto p : pstrList)
    {
        if (*p == "3333")
        {
            std::cout << "找到了" << std::endl;
        }
        std::cout << *p << std::endl;
    }
    for (list<shared_ptr<string>>::iterator itr = pstrList.begin(); itr != pstrList.end(); ++itr)
    {
        if (**itr == "3333")
        {
            cout << **itr << endl;
            pstrList.erase(itr);
        }
    }

    std::cout << "-------------after remove------------" << std::endl;
    for (auto p : pstrList)
    {
        cout << *p << endl;
    }
    system("pasue");
    return 0;
}
