#include <iostream>
#include <memory>

// float*
class my_unique_ptr {
 public:
  my_unique_ptr() { ptr_ = nullptr; };
  my_unique_ptr(float* ptr) { ptr_ = ptr; }

  ~my_unique_ptr() {
    if (ptr_ != nullptr) delete ptr_;
  }

  operator bool() {  //bool操作符重载
    return ptr_ != nullptr;
  }

 private:
  float* ptr_;
};

//智能指针的本质就是让申请的内存空间的生命周期和一个类对象绑定
int main() {
  //创建
  std::shared_ptr<float> p1;  //默认创建的是空指针
  std::shared_ptr<float> p2(
      new float(1));  //创建一个new，分配一个值的空间，初始化为1

  std::shared_ptr<float> p3 = std::make_shared<float>();  //等于new float()

  //使用
  std::cout << *p2 << std::endl;  //同一般指针一样解引用使用
  if (p2) std::cout << "p2不为空" << std::endl;//即bool操作符重载
  return 0;
}