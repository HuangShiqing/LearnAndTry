#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Example {
public:
    Example(int param = 0) {
        number = param;
        std::cout << "Example: " << number << std::endl;
    }

    ~Example() {
        std::cout << "~Example: " << number << std::endl;
    }

    void test_print() {
        std::cout << "in test print: number = " << number << std::endl;
    }

    void set_number(int num) {
        number = num;
    }

private:
    int number;
};

//值传递方式作为参数
void test811(std::unique_ptr<Example> ptr) {
    ptr->test_print();
}
std::unique_ptr<Example> test91() {
    std::unique_ptr<Example> ptr3_2(new Example(32));  // Example:32（输出内容）
    ptr3_2->test_print();                              // in test print: number = 32（输出内容）
    return ptr3_2;                                     // TODO:为什么报错
}
//地址方式作为参数
void test82(std::unique_ptr<Example>* ptr) {
    (*ptr)->test_print();
}
//引用方式作为参数
void test83(std::unique_ptr<Example>& ptr) {
    ptr->test_print();
}

//智能指针的本质就是让申请的内存空间的生命周期和一个类对象绑定
int main() {
    // unique_ptr
    // 参考链接 https://blog.csdn.net/albertsh/article/details/82701573?utm_source=blogxgwz9
    //创建
    // std::unique_ptr<Example> p = new Example(0);//无法直接类型转换
    std::unique_ptr<Example> p(new Example(0));  //但是提供了根据指针的构造方法
    // std::unique_ptr<Example> p4 = p;//也不能从一个unique_ptr初始化一个新的unique_ptr
    // std::unique_ptr<Example> p4(p);//也不能从一个unique_ptr初始化一个新的unique_ptr
    std::unique_ptr<Example> p4 = std::move(p);  //可以用移动语义转移老unique_ptr维护的原始指针到新的unique_ptr,老的失效
    // std::unique_ptr<Example> p = std::make_unique<Example>(0);//make_unique要在c++14中才支持

    // 使用1 get
    if (p.get()) {  //调用get函数，判断内部指针的有效性
        p.get()->test_print();
    }
    // 使用2 operator bool
    if (p)  //大概的实现就是return this->get() != nullptr;
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
    p.reset();    // reset空则释放原内部对象
    // 使用7 swap
    std::unique_ptr<Example> p6(new Example(5));
    p.swap(p6);  //两个智能指针对象的内部指针对象进行了交换

    // 使用8.1.1 值传递的方式作为参数
    // test(p);//不能使用Operator=语义
    test811(std::move(p));  //只能使用move语义进行值传递方式作为参数
    // 使用8.2 地址方式作为参数
    test82(&p);
    // 使用8.3 引用方式作为参数
    test83(p);

    // 隐式的包含了std::move
    // 使用9.1 作为返回值
    std::unique_ptr<Example> p7 = test91();
    // 使用9.2 vector
    std::vector<std::unique_ptr<Example>> vp(5);
    vp[0] = std::unique_ptr<Example>(new Example(56));  //虽然是用了=语义,但是在vector中隐形的包含std::move
    vp.push_back(std::unique_ptr<Example>(new Example(57)));
}