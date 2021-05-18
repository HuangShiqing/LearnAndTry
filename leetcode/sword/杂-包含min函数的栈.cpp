// 剑指 Offer 30. 包含min函数的栈
// 定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，调用 min、push 及 pop 的时间复杂度都是 O(1)。

// 示例:
// MinStack minStack = new MinStack();
// minStack.push(-2);
// minStack.push(0);
// minStack.push(-3);
// minStack.min();   --> 返回 -3.
// minStack.pop();
// minStack.top();      --> 返回 0.
// minStack.min();   --> 返回 -2.

// -------------------第三次刷-----------------------
// 2021年5月13日15:58:35
// 准备第一次社招
// 思路: 两个stack, s1正常用, s2和s1一样高, 专门保存最小值
#include <stack>
using namespace std;

class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> s1;
    stack<int> s2;
    MinStack() {

    }
    
    void push(int x) {
        s1.push(x);
        if(s2.size()){
            if(x<s2.top())
                s2.push(x);
            else
                s2.push(s2.top());            
        }
        else
            s2.push(x);
    }
    
    void pop() {        
        s1.pop();
        s2.pop();
    }
    
    int top() {
        return s1.top();
    }
    
    int min() {
        return s2.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */



//page 165
#include <iostream>
#include <stack>
using namespace std;

// class Solution
// {
// public:
//     stack<int> s_1;
//     stack<int> s_2;

//     void push(int value)
//     {
//         s_1.push(value);
//         if (s_2.size() == 0 || value < s_2.top())
//             s_2.push(value);
//         else
//             s_2.push(s_2.top());
//     }
//     void pop()
//     {
//         assert(s_1.size() > 0 && s_2.size() > 0);

//         s_1.pop();
//         s_2.pop();
//     }
//     int top()
//     {
//         return s_1.top();
//     }
//     int min()
//     {
//         return s_2.top();
//     }
// };
class Solution
{
public:
    stack<int> s1;
    stack<int> s2;
    void push(int value)
    {
        s1.push(value);
        if (s2.size())
        {
            if (value < s2.top())
                s2.push(value);
            else
                s2.push(s2.top());
        }
        else
            s2.push(value);
    }
    void pop()
    {
        if(s1.size())
        {
            s1.pop();
            s2.pop();
        }
    }
    int top()
    {
        if(s1.size())
            return s1.top();
        else
            return -1;
    }
    int min()
    {
        if(s2.size())
            return s2.top();
        else
            return -1;
    }
};

int main()
{
    int min = 10;
    Solution solution;
    solution.push(3);
    min = solution.min();
    solution.push(4);
    min = solution.min();
    solution.push(2);
    min = solution.min();
    solution.push(3);
    min = solution.min();
    solution.pop();
    min = solution.min();
    solution.pop();
    min = solution.min();
    solution.pop();
    min = solution.min();
    solution.push(0);
    min = solution.min();

    return 0;
}