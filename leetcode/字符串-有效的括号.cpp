// 20. 有效的括号
// 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
// 有效字符串需满足：
// 左括号必须用相同类型的右括号闭合。
// 左括号必须以正确的顺序闭合。

// 示例 1：
// 输入：s = "()"
// 输出：true

// 示例 2：
// 输入：s = "()[]{}"
// 输出：true

// 示例 3：
// 输入：s = "(]"
// 输出：false

// 示例 4：
// 输入：s = "([)]"
// 输出：false

// 示例 5：
// 输入：s = "{[]}"
// 输出：true

// -------------------第二次刷-----------------------
// 2021年6月8日15:55:01
// 准备第一次社招
// 思路: 用stack来做, 遍历, 如果遇到是左括号, 则无脑push到stack, 如果是右括号, 则判断stack的情况, 如果stk的栈顶不是对应的左括号或者栈是空的则return false
// 注意可能的情况, 不一定是嵌套的{[]}, 可能是前后成对的{}[]

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