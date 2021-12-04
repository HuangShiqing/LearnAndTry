#include <iostream>
using namespace std;
// 一、虚函数
// 目的: 定义他为虚函数是为了允许用基类的指针来调用子类的这个函数.
// 实现: 虚函数的实现是在类的对象空间中包含一个隐藏的虚函数表, 这个虚函数表的本质就是一个
// 函数指针数组, 这个数组按序存放着这个类对象的多个虚函数实现的真实地址

// 包含虚函数指针和虚函数表, 指针就是函数指针, 表就是数组. 虚函数表是每个类维护一份, 虚函数指针是每个对象维护一份. 
// 因为这个父类指针可以指向子类, 也可能指向父类, 这样只要修改虚函数指针指向父类的虚函数表即可
class father {
 private:
  /* data */
 public:
  father(/* args */);
  ~father();
  //父类中定义虚函数
  virtual void father_virtual_fun() { std::cout << "father" << std::endl; }
};

father::father(/* args */) {}

father::~father() {}

class son : public father {
 private:
  /* data */
 public:
  son(/* args */);
  ~son();
  //子类中重写父类的虚函数，virtual可不加，但是为了明显就加上
  virtual void father_virtual_fun() { std::cout << "son" << std::endl; }
};

son::son(/* args */) {}

son::~son() {}

int main() {
  //用父类指针指向子类
  son son;
  father* p_father = &son;
  //打印的是son，证明调用的是子类的方法
  p_father->father_virtual_fun();
  return 0;
}

// 二、纯虚函数
// 目的: 定义纯虚函数是为了实现一个接口，起到一个规范的作用，规范继承这个类的程序员必须实现这个函数
// 称带有纯虚函数的类为抽象类。不能创建类的实例，只能创建它的派生类的实例。
class Animal {
 private:
  /* data */
 public:
  // 表明派生类必须有一个参数为weigth的eat实现
  virtual void eat(int weight) = 0;
};