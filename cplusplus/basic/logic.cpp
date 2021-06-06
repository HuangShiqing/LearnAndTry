// 逻辑运算符的短路性质。
// 以逻辑运算符 && 为例，对于 A && B 这个表达式，如果 A 表达式返回False ，那么 A && B 已经确定为False ，此时不会去执行表达式 B。
// 同理，对于逻辑运算符 ||， 对于 A || B 这个表达式，如果 A 表达式返回 True ，那么 A || B 已经确定为 True ，此时不会去执行表达式 B。
#include <iostream>
using namespace std;

bool fun1(){
    cout<<"hi from fun1"<<endl;
    return true;
}

int main(){
    if(true && fun1()) // 会执行后面的fun1
        cout<<"test"<<endl;    
    if(false || fun1()) // 会执行后面的fun1
        cout<<"test1"<<endl; 

    if(true || fun1()) // 发现前面已经为True了, 不管后面为啥输出都为True, 因此不会执行后面的fun1
        cout<<"test2"<<endl;
    if(false && fun1()) // 发现前面已经为False了, 不管后面为啥输出都为False, 因此不会执行后面的fun1
        cout<<"test3"<<endl; 
    
    return 0;
}