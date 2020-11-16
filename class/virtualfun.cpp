#include <iostream>
using namespace std;
// 定义他为虚函数是为了允许用基类的指针来调用子类的这个函数。、

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