#include <iostream>
#include <stack>
using namespace std;


int main()
{
    //栈的初始化
    stack<int> s;

    //从尾部插入
    s.push(5);

    //访问头
    int num = s.top();

    //从尾部删除
    s.pop();

    return 0;
}