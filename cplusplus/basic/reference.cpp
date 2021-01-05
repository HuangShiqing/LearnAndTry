#include <iostream>
using namespace std;
// 引用是别名，指针是地址
// 1.指针在运行时可以改变所指向的值，而引用一旦与某个对象绑定后就不再改变。
// 2.内存上看，指针变量分配区域，而不为引用分配内存区域。
// 3.因为引用生命时必须初始化，从而指向一个已经存在的对象，引用不能为空值。
// 4.可以有指针的指针，但是没有引用的引用。效率上一样的

//值传递
void swap(float a, float b) {
  float temp = a;
  a = b;
  b = temp;
}
//指针做参数
void swap2(float* a, float* b) {
  float temp = *a;
  *a = *b;
  *b = temp;
}
//引用，好处是代码结构与值传递一样
void swap3(float& a, float& b) {
  float temp = a;
  a = b;
  b = temp;
}

//不要返回局部变量引用
// float& test()
// {
//   float a = 10;
//   return a;
// }

// 1.可以返回静态变量引用
// 2.函数的返回是引用，则函数可以作为左值
float& test2() {
  static float a = 10;
  return a;
}

void show(const float& a) {//常量引用作为参数，防止函数内误操作导致外面也变了
  // a = 1;//修改常量引用会报错
  std::cout << a << std::endl;
}

int main() {
  int a = 0;   //创建被引用的对象
  int& b = a;  //引用初始化后指向的对象不可更改
  // int &b;//定义时必须初始化
  int c = 1;
  b = c;  //赋值操作，把b和a指向的内存赋值为c，不是更改b的指向

  // int& d = 10;//错误，非常量引用的初始化必须为左值
  const int& d = 10;  //这样可以，编译器自动添加了一个temp

  float& ref = test2();
  std::cout << ref << std::endl;  //获取到静态变量的值
  test2() = 100;  //函数的返回作为左值被100更改了值
  std::cout << ref << std::endl;  //静态变量同样也被更改
  return 0;
}