#include <iostream>
using namespace  std;

class Person{
public:
    Person(int a =1,int b=2):num(a),age(b){

    }
    ~Person(){

    }


public:
    int num;
    int age;
};
int main() {
    Person p;
    std::cout<<p.num<<endl<<p.age<<endl;
    std::cout << "Hello, World!" << std::endl;
    return 0; 
}
