#include <iostream>

//成员变量和成员函数是分开存储的

class Person
{

};

class Person2
{
    int mA;//每个实例都会安排一个位置放非静态成员变量mA
    static int mB;//静态成员变量不占实例的空间
    void fun(){};//成员函数不占实例的空间,非静态的也不占
    static void fun2(){};//成员函数不占实例的空间
};

void test()
{
    Person p;//空对象
    std::cout<<sizeof(p)<<std::endl;//空对象所占空间为1字节

    Person2 p2;
    std::cout<<sizeof(p2)<<std::endl;//所占空间为4字节
}