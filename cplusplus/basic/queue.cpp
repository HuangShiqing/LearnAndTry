#include <iostream>
#include <queue>
using namespace std;

// queue队列只能从尾插入从头弹出, 访问是可以两头访问的
// deque双端队列可以任何操作都可以对头尾进行, 包括访问, 插入, 弹出
int main(){
    // 初始化
    queue<int> q;
    
    // 插入
    // 插入尾
    q.push(1);

    // 访问
    //访问头
    int num = q.front();
    //访问尾
    num = q.back();

    // 弹出
    // 弹出头
    q.pop();

    // 获得信息
    if(q.empty())
        return 0;
    num = q.size();
    
    return 0;
}