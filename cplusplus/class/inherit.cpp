#include "inherit.hpp"

father::father(/* args */) {}

father::~father() {}

son::son(/* args */) {}

son::~son() {}

int main() {
  father father;
  // 类对象只能访问本身的public成员
  int a = father.father_public_param;
  int b = father.father_public_fun();
  // int c=father.father_protected_param;
  // int c=father.father_private_param;
  son son1;
  //子类对象只能访问父类public成员，即权限和父类对象一样
  int c = son1.father_public_param;
  int d = son1.father_public_fun();
}
