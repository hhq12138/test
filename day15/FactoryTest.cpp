#include <iostream>

using namespace std;
// 鞋子抽象类
class Shoes
{
public:
    virtual ~Shoes() {}
    virtual void Show() = 0;
};

// 耐克鞋子
class NiKeShoes : public Shoes
{
public:
    void Show()
    {
        std::cout << "我是耐克球鞋，我的广告语：Just do it" << std::endl;
    }
};

// 阿迪达斯鞋子
class AdidasShoes : public Shoes
{
public:
    void Show()
    {
        std::cout << "我是阿迪达斯球鞋，我的广告语:Impossible is nothing" << std::endl;
    }
};

enum SHOES_TYPE
{
    NIKE,
    ADIDAS
};

// 总鞋厂
class ShoesFactory
{
public:
    // 根据鞋子类型创建对应的鞋子对象
    Shoes *CreateShoes(SHOES_TYPE type)
    {
        switch (type)
        {
        case NIKE:
            return new NiKeShoes();
            break;
        case ADIDAS:
            return new AdidasShoes();
            break;
        default:
            return NULL;
            break;
        }
    }
};

int main(int argc, const char *argv[])
{
    ShoesFactory shoesFactory;

    // 从鞋工厂对象创建耐克鞋对象
    Shoes *pNikeShoes = shoesFactory.CreateShoes(NIKE);
    if (pNikeShoes != NULL)
    {
        // 耐克球鞋广告喊起
        pNikeShoes->Show();

        // 释放资源
        delete pNikeShoes;
        pNikeShoes = NULL;
    }

    // 从鞋工厂对象创建阿迪达斯鞋对象
    Shoes *pAdidasShoes = shoesFactory.CreateShoes(ADIDAS);
    if (pAdidasShoes != NULL)
    {
        // 阿里达斯球鞋广告喊起
        pAdidasShoes->Show();

        // 释放资源
        delete pAdidasShoes;
        pAdidasShoes = NULL;
    }

    return 0;
}