//page 69
#include <stack>
using namespace std;

class Solution
{
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
    void push(int node)
    {
        stack1.push(node);
    }

    int pop()
    {
        int r;
        if (stack2.size())
        {
            r = stack2.top();
            stack2.pop();
        }
        else
        {
            while (stack1.size())
            {
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