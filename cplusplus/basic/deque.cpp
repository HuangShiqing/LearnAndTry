#include <iostream>
#include <deque>
using namespace std;

int main()
{
    //初始化空队列
    deque<int> dq;

    //插入
    //从尾部插入
    dq.push_back(5);
    //从头部插入
    dq.push_front(1);

    //访问
    //访问头
    int num = dq.front();
    //访问尾
    num = dq.back();

    //删除
    //删除头
    dq.pop_front();
    //删除尾
    dq.pop_back();

    return 0;

}