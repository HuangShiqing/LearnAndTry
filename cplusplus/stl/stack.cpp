#include <iostream>
#include <stack>
using namespace std;


int main()
{
    //栈的初始化
    stack<int> s;

    //从尾部插入
    s.push(5);

    //访问栈顶
    int num = s.top();
    //top不支持访问空栈
    if(s.size())
        num = s.top();

    //弹出栈顶
    s.pop();

    return 0;
}