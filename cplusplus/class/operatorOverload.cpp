//操作符重载
//1.成员函数实现操作符重载
//2.全局函数实现操作符重载
//3.重载函数也可以发生函数重载

class Person{
    public:
    // 1.成员函数实现操作符重载
    Person operator+(Person& p1){
        Person p3;
        p3.m_age = this->m_age+p1.m_age;
        return p3;
    };
    //3.重载函数也可以发生函数重载
    Person operator+(int a){
        Person p3;
        p3.m_age = this->m_age+a;
        return p3;
    };
    int m_age;
};

//2.全局函数实现操作符重载
// Person operator+(Person& p1, Person& p2)
// {
//     Person p3;
//     p3.m_age = p1.m_age+p2.m_age;
//     return p3;
// }



int main()
{
    Person p1;
    p1.m_age = 10;
    Person p2;
    p2.m_age = 20;

    Person p3 = p1 + p2;
    return 0;
}