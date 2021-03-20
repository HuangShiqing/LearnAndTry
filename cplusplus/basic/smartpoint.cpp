#include <iostream>
#include <memory>
#include <vector>

// float*
class my_unique_ptr {
 public:
  my_unique_ptr() { ptr_ = nullptr; };
  my_unique_ptr(float* ptr) { ptr_ = ptr; }

  ~my_unique_ptr() {
    if (ptr_ != nullptr) delete ptr_;
  }

  operator bool() {  // bool操作符重载
    return ptr_ != nullptr;
  }

 private:
  float* ptr_;
};

class Example {
 public:
  Example(int param = 0) {
    number = param;
    std::cout << "Example: " << number << std::endl;
  }

  ~Example() { std::cout << "~Example: " << number << std::endl; }

  void test_print() {
    std::cout << "in test print: number = " << number << std::endl;
  }

  void set_number(int num) { number = num; }

 private:
  int number;
};


//值传递方式作为参数
void test811(std::unique_ptr<Example> ptr)
{
  ptr->test_print();
} 
std::unique_ptr<Example> test91()
{
 std::unique_ptr<Example> ptr3_2(new Example(32));// Example:32（输出内容）
 ptr3_2->test_print();                       // in test print: number = 32（输出内容）
 return ptr3_2;//TODO:为什么报错
}
//地址方式作为参数
void test82(std::unique_ptr<Example>* ptr)
{
  (*ptr)->test_print();
} 
//引用方式作为参数
void test83(std::unique_ptr<Example>& ptr)
{
  ptr->test_print();
} 

//做参数,隐式的有一句浅拷贝 局部变量ptr = 全局变量ptr,++,因此在函数内部use_count=2,函数退出释放局部变量,--
void test91(std::shared_ptr<Example> ptr6_1)
{
 ptr6_1->test_print();       // in test print: number = 6（输出内容）
 std::cout << "ptr6_1 use count : " << ptr6_1.use_count() << std::endl;// ptr6 use count : 2（输出内容）
}

//地址传递作为参数,use_count不变
void test92(std::shared_ptr<Example>* ptr6_1)
{
 (*ptr6_1)->test_print();       // in test print: number = 6（输出内容）
}

//引用方式 作为参数,use_count不变
void test93(std::shared_ptr<Example>& ptr6_1)
{
 ptr6_1->test_print();       // in test print: number = 6（输出内容）
}

//做返回值
std::shared_ptr<Example> test92()
{
 std::shared_ptr<Example> ptr6_2(new Example(62));    // Example:62（输出内容）
 ptr6_2->test_print();           // in test print: number = 62（输出内容）
 std::cout << "ptr6_2 use count : " << ptr6_2.use_count() << std::endl;// ptr6_2 use count : 1（输出内容）
 return ptr6_2;
}



class CB;
class CA
{
public:
    CA() { std::cout << "CA() called! " << std::endl; }
    ~CA() { std::cout << "~CA() called! " << std::endl; }
    void set_ptr(std::shared_ptr<CB>& ptr) { m_ptr_b = ptr; }
    void b_use_count() { std::cout << "b use count : " << m_ptr_b.use_count() << std::endl; }
    void show() { std::cout << "this is class CA!" << std::endl; }
private:
    std::shared_ptr<CB> m_ptr_b;
};

class CB
{
public:
    CB() { std::cout << "CB() called! " << std::endl; }
    ~CB() { std::cout << "~CB() called! " << std::endl; }
    void set_ptr(std::shared_ptr<CA>& ptr) { m_ptr_a = ptr; }
    void a_use_count() { std::cout << "a use count : " << m_ptr_a.use_count() << std::endl; }
    void show() { std::cout << "this is class CB!" << std::endl; }
private:
    std::shared_ptr<CA> m_ptr_a;
};

void test_refer_to_each_other()
{
    std::shared_ptr<CA> ptr_a(new CA());
    std::shared_ptr<CB> ptr_b(new CB());
    //计数都为1
    std::cout << "a use count : " << ptr_a.use_count() << std::endl;
    std::cout << "b use count : " << ptr_b.use_count() << std::endl;
    //计数增加
    ptr_a->set_ptr(ptr_b);
    ptr_b->set_ptr(ptr_a);
    //计数都为2
    std::cout << "a use count : " << ptr_a.use_count() << std::endl;
    std::cout << "b use count : " << ptr_b.use_count() << std::endl;
    //函数退出计数减一却仍然大于0不会析构,原因就是循环引用
}

//智能指针的本质就是让申请的内存空间的生命周期和一个类对象绑定
int main() {
  //unique_ptr
  // 参考链接 https://blog.csdn.net/albertsh/article/details/82701573?utm_source=blogxgwz9
  //创建
  // std::unique_ptr<Example> p = new Example(0);//无法直接类型转换
  std::unique_ptr<Example> p(new Example(0));//但是提供了根据指针的构造方法
  // std::unique_ptr<Example> p4 = p;//也不能从一个unique_ptr初始化一个新的unique_ptr
  // std::unique_ptr<Example> p4(p);//也不能从一个unique_ptr初始化一个新的unique_ptr
  std::unique_ptr<Example> p4 = std::move(p);//可以用移动语义转移老unique_ptr维护的原始指针到新的unique_ptr,老的失效
  // std::unique_ptr<Example> p = std::make_unique<Example>(0);//make_unique要在c++14中才支持 

  // 使用1 get
  if (p.get()) {  //调用get函数，判断内部指针的有效性
    p.get()->test_print();
  }
  // 使用2 operator bool
  if(p)//大概的实现就是return this->get() != nullptr;
    std::cout << "p is valid" << std::endl; 

  // 使用3 operator*
  (*p).test_print();
  // 使用4 operator->
  p->test_print();

  // 使用5 release
  Example* p5 = p.release();  //调用release函数,将智能指针和内部指针分离.
  // 使用6 reset
  p.reset(p5);  //重新设置智能指针管理的内部指针.如果设置之前智能指针已经管理
                //了一个对象那么在设置之后原来的对象会被析构掉
  p.reset(); //reset空则释放原内部对象
  // 使用7 swap
  std::unique_ptr<Example> p6(new Example(5));
  p.swap(p6);//两个智能指针对象的内部指针对象进行了交换

  // 使用8.1.1 值传递的方式作为参数
  // test(p);//不能使用Operator=语义
  test811(std::move(p));//只能使用move语义进行值传递方式作为参数
  // 使用8.2 引用方式作为参数
  test82(&p);
  // 使用8.3 地址方式作为参数
  test83(p);

  // 隐式的包含了std::move
  // 使用9.1 作为返回值
  std::unique_ptr<Example> p7 = test91();
  // 使用9.2 vector
  std::vector<std::unique_ptr<Example>> vp(5);
  vp[0] = std::unique_ptr<Example>(new Example(56));//虽然是用了=语义,但是在vector中隐形的包含std::move
  vp.push_back(std::unique_ptr<Example>(new Example(57)));

  // ------------------分割线------------------
  // shared_ptr  
  // 参考链接https://blog.csdn.net/albertsh/article/details/81807927
  //创建
  std::shared_ptr<Example> p8;  //默认创建的是空指针
  std::shared_ptr<Example> p9(new Example(1));  //创建一个new，分配一个值的空间，初始化为1
  std::shared_ptr<Example> p10 = std::make_shared<Example>(1);  //等于new Example(1)

  // 使用1 use_count 初始化后为1
  std::cout<<p8.use_count()<<std::endl;

  // 使用2 unique  实现基本就是return this->use_count() == 1
  if(p8.unique())
    std::cout<<"unique"<<std::endl;

  // 使用3 operator= 增加引用,use_count++
  std::shared_ptr<Example> p11 = p8;

  // 使用4 reset 减少引用,use_count--
  // 用于重新设置内部对象，若参数为空，则表示取消对内部对象的引用，
  // 此时若引用计数大于1则进行减1操作，否则直接析构内部对象

  //使用5 不可用同一对象指针生成两个shared_ptr对象

  // 使用6.1 值传递的方式作为参数
  test91(p8);
  // 使用6.2 地址传递的方式作为参数
  test92(&p8);
  // 使用6.3 引用方式作为参数
  test93(p8);
  // 使用7 做返回值
  std::shared_ptr<Example> p12 = test92();//局部的释放了,外面的接收了,里面use_count都是1

  // 使用8 vector
  std::vector<std::shared_ptr<Example>> vp2(2);
  vp2[0] = p12;//增加引用计数,++
  vp2.push_back(p12);//增加引用计数,++


  // ------------------分割线------------------
  // weak_ptr 
  // 参考链接https://blog.csdn.net/albertsh/article/details/82286999
  //shared_ptr循环引用问题,shared_ptr管理的指针的成员属性为另一个shared_ptr
  test_refer_to_each_other();//不会析构

  // 创建,不会增加引用计数
  // 本身不能直接定义指向原始指针的对象，只能指向shared_ptr对象
  std::shared_ptr<CA> ptr_1(new CA());
  std::cout << "ptr_1 use count : " << ptr_1.use_count() << std::endl; // 输出：ptr_1 use count : 1
  std::weak_ptr<CA> wk_ptr = ptr_1;//不会增加引用计数
  std::cout << "ptr_1 use count : " << ptr_1.use_count() << std::endl; // 输出：ptr_1 use count : 1
  
  // 使用 expired,lock
  if(wk_ptr.expired())
    wk_ptr.lock()->show();
  return 0;
}