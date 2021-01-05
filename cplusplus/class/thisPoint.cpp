// this指针指向实例
// this指针的作用:
// 1.形参和成员变量同名时做区分
// 2.返回实例本身

#include <iostream>
using namespace std;

class Person{
public:
    void fun(int age)
    {
        // age=age;
        this->age = age;//this指针指向实例,可用于区分同名形参和成员变量,本质上属性的访问
                        //都是省略了this
    }

    Person& fun2(){
        return *this;//返回实例本身
    }

    void fun3(){
        std::cout<<"hello"<<std::endl;
    }

    int age;
};

int main() {
  Person* p = nullptr;
  p->fun3();//指向空的类指针调用成员函数是可行的,前提是函数内没有隐含的this指针
  return 0;
}

