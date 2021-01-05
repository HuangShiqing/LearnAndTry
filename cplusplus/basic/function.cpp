#include <iostream>
using namespace std;

// 1.有一个参数带默认值，则后面的所有参数都必须带默认值
int add(int a, int b = 1, int c = 2) { 
    return a + b + c; 
}

// 2.声明和实现只能有一个地方设置默认值
int add2(int a, int b = 1, int c = 2);
int add2(int a, int b, int c) { 
    return a + b + c; 
}

// 3.只设置类型不设置形参即为占位参数，并可设置默认值
int add3(int a, int, int =  2){
    return a;
}

int main() { 
    return 0; 
}