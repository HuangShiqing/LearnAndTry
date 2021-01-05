#include <iostream>
using namespace std;

// 一:函数重载的条件
// 1.同一个作用域
// 2.函数名相同
// 3.参数类型、参数顺序、参数个数不同
// 4.返回值不同不行
int func(int a, float b)
{
    std::cout<<"func(int a, float b)"<<std::endl;
    return 0;
}
//个数不同，为了与下面的引用不冲突，注释掉这个函数
// int func(int a)
// {
//     std::cout<<"func(int a)"<<std::endl;
//     return 0;
// }
//类型不同
int func(int a, int b)
{
    std::cout<<"func(int a, int b)"<<std::endl;
    return 0;
}
//顺序不同，本质还是类型不同
int func(float a, int b)
{
    std::cout<<"func(float a, int b)"<<std::endl;
    return 0;
}
//返回值类型不同不行
// float func(int a, float b)
// {
//     std::cout<<"func(int a, float b)"<<std::endl;
//     return 0;
// }



// 二:引用与重载
// 引用可以认为是类型不同，不调用编译不报错，但是运行func(a)时会与fun(int a)发生二义性报错
int func(int& a){
    std::cout<<"func(int& a)"<<std::endl;
    return 0;
}
// 常量引用和普通引用也可以重载，同样认为是类型不同，不调用编译不报错，但是运行func(a)时会与fun(int a)发生二义性报错
int func(const int& a){
    std::cout<<"func(int& a)"<<std::endl;
    return 0;
}


// 三:默认函数与重载。一般重载不用默认参数
// 下面两个函数是认为是参数个数不同，不调用不出错，但是当func3(a)时会发生二义性错误，因此一般重载不用默认参数
int func3(int a, int b = 10){
    std::cout<<"func3(int a, int b = 10)"<<std::endl;
    return 0;
}
int func3(int a){
    std::cout<<"func3(int a)"<<std::endl;
    return 0;
}


int main() { 
    int a = 10;
    func(a);//传入的是可读可写的，因此是func(int& a)
    func(10);//传入的是只读的，因此是func(const int& a)
    return 0; 
}