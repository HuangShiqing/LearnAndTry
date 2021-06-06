// page 69
#include <stack>
using namespace std;

class Solution {
public:
    // void push(int node)
    // {
    //     stack1.push(node);
    // }

    // int pop()
    // {
    //     if (stack2.size() <= 0)
    //     {
    //         while (stack1.size() > 0)
    //         {
    //             int temp = stack1.top();
    //             stack1.pop();
    //             stack2.push(temp);
    //         }
    //     }

    //     int head = stack2.top();
    //     stack2.pop();
    //     return head;
    // }
    //弹出：当s2非空时，直接弹出s2，当s2为空时将s1的内容逐一push到s2中
    //压入：在s1中压入
    void push(int node) { stack1.push(node); }

    int pop() {
        int r;
        if (stack2.size()) {
            r = stack2.top();
            stack2.pop();
        } else {
            while (stack1.size()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
            r = stack2.top();
            stack2.pop();
        }
        return r;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};

// 剑指 Offer 09. 用两个栈实现队列
// 用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead
// ，分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 -1 )
// 示例 1：
// 输入：
// ["CQueue","appendTail","deleteHead","deleteHead"]
// [[],[3],[],[]]
// 输出：[null,null,3,-1]
// 示例 2：
// 输入：
// ["CQueue","deleteHead","appendTail","appendTail","deleteHead","deleteHead"]
// [[],[],[5],[2],[],[]]
// 输出：[null,-1,null,null,5,2]

// 2021年04月24日22:11:47
// 准备第一次社招
// 思路:
// 要求用栈来实现队列, 难点在于实现队列的出队, 因为栈没办法直接访问到最先入栈的第一个元素
// 所以用两个栈, 要求出队时就把第一个栈的所有元素都pop到第二个栈, 然后第二个栈再pop一下就是把第一个入队元素出队

class CQueue {
public:
    stack<int> s1;
    stack<int> s2;
    CQueue() {

    }

    void appendTail(int value) {
        s1.push(value);
    }

    int deleteHead() {
        int r;
        if(!s2.empty()){
            r =  s2.top();
            s2.pop();
        }
        else{
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
            r =  s2.top();
            s2.pop();
        }
        return r;
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */