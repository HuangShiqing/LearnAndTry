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