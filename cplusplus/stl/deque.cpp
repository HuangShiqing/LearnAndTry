#include <iostream>
#include <deque>
using namespace std;

// queue队列只能从尾插入从头弹出, 访问是可以两头访问的
// deque双端队列可以任何操作都可以对头尾进行, 包括访问, 插入, 弹出
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

    // 获得信息
    if(dq.empty())
        return 0;
    num = dq.size();

    return 0;

}