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

//做参数,隐式的有一句浅拷贝 局部变量ptr = 全局变量ptr,++,因此在函数内部use_count=2,函数退出释放局部变量,--
void test91(std::shared_ptr<Example> ptr6_1) {
    ptr6_1->test_print();  // in test print: number = 6（输出内容）
    std::cout << "ptr6_1 use count : " << ptr6_1.use_count() << std::endl;  // ptr6 use count : 2（输出内容）
}

//地址传递作为参数,use_count不变
void test92(std::shared_ptr<Example>* ptr6_1) {
    (*ptr6_1)->test_print();  // in test print: number = 6（输出内容）
}

//引用方式 作为参数,use_count不变
void test93(std::shared_ptr<Example>& ptr6_1) {
    ptr6_1->test_print();  // in test print: number = 6（输出内容）
}

//做返回值
std::shared_ptr<Example> test92() {
    std::shared_ptr<Example> ptr6_2(new Example(62));  // Example:62（输出内容）
    ptr6_2->test_print();                              // in test print: number = 62（输出内容）
    std::cout << "ptr6_2 use count : " << ptr6_2.use_count() << std::endl;  // ptr6_2 use count : 1（输出内容）
    return ptr6_2;
}

int main(int argc, char const* argv[]) {
    // 参考链接https://blog.csdn.net/albertsh/article/details/81807927
    //创建
    std::shared_ptr<Example> p8;                  //默认创建的是空指针
    std::shared_ptr<Example> p9(new Example(1));  //创建一个new，分配一个值的空间，初始化为1
    std::shared_ptr<Example> p10 = std::make_shared<Example>(1);  //等于new Example(1)

    // 使用1 use_count 初始化后为1
    std::cout << p8.use_count() << std::endl;

    // 使用2 unique  实现基本就是return this->use_count() == 1
    if (p8.unique())
        std::cout << "unique" << std::endl;

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
    std::shared_ptr<Example> p12 = test92();  //局部的释放了,外面的接收了,里面use_count都是1

    // 使用8 vector
    std::vector<std::shared_ptr<Example>> vp2(2);
    vp2[0] = p12;        //增加引用计数,++
    vp2.push_back(p12);  //增加引用计数,++

    return 0;
}
