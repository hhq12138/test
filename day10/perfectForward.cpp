#include<iostream>
#include<vector>
using namespace std;

void Fun(int &a){
    cout<<"左值引用"<<endl;
}

void Fun(int &&a){
    cout<<"右值引用"<<endl;
}

template<typename T>
void perfectForward(T &&t){
    Fun(forward<T>(t));
}
int main(int argc,char *argv[]) {
    perfectForward(10);
   return 0;
}

