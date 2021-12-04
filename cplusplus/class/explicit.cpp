// explicit关键字只能用于修饰只有一个参数的类构造函数, 它的作用是表明该构造函数是显示的, 而非隐式的
// 类构造函数默认情况下即声明为implicit(隐式)
// explicit关键字只对有一个参数的类构造函数有效或者除了第一个参数以外的其他参数都有默认值

// https://www.cnblogs.com/rednodel/p/9299251.html

// [隐式构造可能存在的问题](https://www.shangmayuan.com/a/6b16d01233494022be9eaea3.html)

// 构造函数分类和调用方法
// 1.括号法调用构造函数
// 2.显式法调用构造函数
// 3.隐式转换法

class Person {
public:
    Person(int a){
        //有参普通构造函数
    };
};
//   3.隐式转换法
Person p7 = 1;  //相当于 Person p7 = Person(1);

class Person2 {
public:
    explicit Person2(int a){
        //有参普通构造函数
    };
};
//   3.隐式转换法
// Person2 p8 = 1;  //报错