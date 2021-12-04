// https://www.cnblogs.com/yongdaimi/p/9565996.html

// mutable是const的反义词, 
// const成员函数确保了成员变量不能在该函数中被修改
// 但是对于特定成员变量, 我希望能在const成员函数进行修改, 同时仍然确保其他成员变量不能被修改 

#include <iostream>

class Person {
public:
    Person();
    ~Person();

    int getAge() const; /*调用方法*/
    int getCallingTimes() const; /*获取上面的getAge()方法被调用了多少次*/
private:
    int age;
    mutable int m_nums;/*用于统计getAge函数的被调用次数*/
    int m_nums2;
};

int Person::getAge() const
{
    std::cout << "Calling the method" << std::endl;
    m_nums++;//只有mutable可以修改
    // m_nums2++;//这个非mutable是无法修改的
    return age;
}