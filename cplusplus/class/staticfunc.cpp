// 一:静态成员变量
// 1.所有实例享有同一份数据
// 2.在编译阶段分配内存空间
// 3.类内声明,类外初始化
// 4.静态成员可以通过类名访问

// 二:静态成员函数
// 1.静态成员函数,所有实例享有同一份
// 2.静态成员函数只能访问静态成员变量
// 3.静态成员可以通过类名访问
class Person
{
public:
    static int mA;//
    const static int mB = 1;//只有const static才能在类内初始化
    int mC;
    static void fun()
    {
        mA = 1;
        // mC = 1;//静态成员函数只能访问静态成员变量
    }
    void fun2()
    {}

};

int main()
{
    Person p;
    p.fun();//一般的访问方法
    Person::fun();//静态成员可以通过类名访问
    Person::mA = 1;
    // Person::fun2();非静态成员函数不行
}