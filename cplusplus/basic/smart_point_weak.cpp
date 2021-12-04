#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class CB;
class CA {
public:
    CA() {
        std::cout << "CA() called! " << std::endl;
    }
    ~CA() {
        std::cout << "~CA() called! " << std::endl;
    }
    void set_ptr(std::shared_ptr<CB>& ptr) {
        m_ptr_b = ptr;
    }
    void b_use_count() {
        std::cout << "b use count : " << m_ptr_b.use_count() << std::endl;
    }
    void show() {
        std::cout << "this is class CA!" << std::endl;
    }

private:
    std::shared_ptr<CB> m_ptr_b;
    // std::weak_ptr<CB> m_ptr_b;//解决循环依赖的办法就是替换成weak指针
};

class CB {
public:
    CB() {
        std::cout << "CB() called! " << std::endl;
    }
    ~CB() {
        std::cout << "~CB() called! " << std::endl;
    }
    void set_ptr(std::shared_ptr<CA>& ptr) {
        m_ptr_a = ptr;
    }
    void a_use_count() {
        std::cout << "a use count : " << m_ptr_a.use_count() << std::endl;
    }
    void show() {
        std::cout << "this is class CB!" << std::endl;
    }

private:
    std::shared_ptr<CA> m_ptr_a;
    // std::weak_ptr<CA> m_ptr_a;//解决循环依赖的办法就是替换成weak指针
};

void test_refer_to_each_other() {
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

int main(int argc, char const* argv[]) {
    // weak_ptr
    // 参考链接https://blog.csdn.net/albertsh/article/details/82286999
    // shared_ptr循环引用问题,shared_ptr管理的指针的成员属性为另一个shared_ptr
    test_refer_to_each_other();  //不会析构

    // 创建,不会增加引用计数
    // 本身不能直接定义指向原始指针的对象，只能指向shared_ptr对象
    std::shared_ptr<CA> ptr_1(new CA());
    std::cout << "ptr_1 use count : " << ptr_1.use_count() << std::endl;  // 输出：ptr_1 use count : 1
    std::weak_ptr<CA> wk_ptr = ptr_1;                                     //不会增加引用计数
    std::cout << "ptr_1 use count : " << ptr_1.use_count() << std::endl;  // 输出：ptr_1 use count : 1

    // 使用 expired,lock
    if (wk_ptr.expired())
        wk_ptr.lock()->show();
    return 0;
}
