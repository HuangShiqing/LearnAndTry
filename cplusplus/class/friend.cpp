#include <iostream>
using namespace std;

//友元的作用是为了让一个类的私有属性可以在类外被访问
// 三种实现方式
// 1.全局函数作友元
// 2.类作友元
// 3.成员函数作友元
class goodgay2;

class Person {
  friend void g_fun(
      Person& p);  //在类里设置该全局函数的声明为友元,可访问该类的私有属性
  friend class goodgay;  //在类里设置另一个类的声明为友元,可访问该类的私有属性
  friend void goodgay2::visit(
      Person& p);  //在类里设置另一个类的成员函数声明为友元,可访问该类的私有属性
 public:
  Person() { m_age = 10; }

 private:
  int m_age;
};

void g_fun(Person& p) {
  int a = p.m_age;  //一般情况无法在实例中访问private属性
}

class goodgay {
 public:
  goodgay() {
    m_p = new Person;
    int a = m_p->m_age;  //在另外一个类里一般无法访问类的私有属性
  }
  void visit() {
    int a = m_p->m_age;  //在另外一个类里一般无法访问类的私有属性
  }
  void visit2(Person& p) {
    int a = p.m_age;  //在另外一个类里一般无法访问类的私有属性
  }

 private:
  Person* m_p;
};

class goodgay2 {
 public:
  void visit(Person& p) {
    int a = p.m_age;  //在另外一个类的成员函数里一般无法访问类的私有属性
  }
};

int main() {
  Person p;
  g_fun(p);

  return 0;
}