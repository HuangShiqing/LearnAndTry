// 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

// 有效字符串需满足：

// 左括号必须用相同类型的右括号闭合。
// 左括号必须以正确的顺序闭合。
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    bool isValid(string s)
    {
        if (s.size() % 2 != 0)
            return false;

        //用map来加快判断是否为右括号和是否对应
        unordered_map<char, char> pairs = {{')', '('}, {']', '['}, {'}', '{'}};
        stack<char> stk;
        for (char c : s)
        {
            if (pairs.count(c)) //如果是右括号
            {
                if (stk.empty() || stk.top() != pairs[c]) //如果stk的栈顶不是对应的左括号或者栈是空的
                {
                    return false;
                }
                stk.pop();
            }
            else
            {
                stk.push(c); //入栈
            }
        }
        if (stk.empty()) //循环完后栈是空的才是正确的
            return true;
        else
        {
            return false;
        }
    }
};