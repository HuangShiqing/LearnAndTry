// 剑指 Offer 31. 栈的压入、弹出序列
// 输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。
// 例如，序列 {1,2,3,4,5} 是某栈的压栈序列，序列 {4,5,3,2,1} 是该压栈序列对应的一个弹出序列，但 {4,3,5,1,2} 就不可能是该压栈序列的弹出序列。

// 示例 1：
// 输入：pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
// 输出：true
// 解释：我们可以按以下顺序执行：
// push(1), push(2), push(3), push(4), pop() -> 4,
// push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1

// 示例 2：
// 输入：pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
// 输出：false
// 解释：1 不能在 2 之前弹出。
 
// 提示：
// 0 <= pushed.length == popped.length <= 1000
// 0 <= pushed[i], popped[i] < 1000
// pushed 是 popped 的排列。

// -------------------第三次刷-----------------------
// 2021年5月13日15:58:35
// 准备第一次社招
// 思路: 我这会儿要弹出的必须是栈顶的. 那么我就建立一个空栈, 遍历弹出的数popped[i], 如果栈顶不等于popped[i], 
// 那么就逐个push pushed里的数, 每push一个就判断是否相等. 如果push完了还没有找到popped[i], 那么就代表false

#include <stack>
using namespace std;

class Solution {
public:
    stack<int> s;
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int j=0;
        for(int i=0;i<popped.size();i++) {
            if(s.top()==popped[i]) {
                s.pop();
            }
            else{
                bool flag = false;//这个false有两个作用, 当pushed里还剩有数时, 需要找到相等的置为true才不算false; 当pushed里没有数时, 如果这行代码上面的==失败, 即代表失败
                while(j<pushed.size()) {
                    s.push(pushed[j]);
                    j++;
                    if(s.top()==popped[i]) {
                        s.pop();         
                        flag=true;
                        break;
                    }
                }
                if(flag==false)
                    return false;
            }
        }
        return true;
    }
};


#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> vector_init(int *p, int len)
{
    vector<int> v(len);
    for (int i = 0; i < len; i++)
        v[i] = p[i];

    return v;
}

class Solution
{
public:
    // bool IsPopOrder(vector<int> pushV, vector<int> popV)
    // {
    //     if (pushV.size() == 0 || popV.size() == 0 || pushV.size() != popV.size())
    //         return false;
    //     else if (pushV.size() == 1)
    //     {
    //         if (pushV[0] == popV[0])
    //             return true;
    //         else
    //             return false;
    //     }

    //     stack<int> s;

    //     int start_index;
    //     for (start_index = 0; start_index < popV.size(); start_index++)
    //     {
    //         if (pushV[start_index] == popV[0])
    //             break;
    //     }
    //     for (int i = 0; i <= start_index; i++)
    //         s.push(pushV[i]);
    //     s.pop();

    //     //判断pushV是否有pushV[1]
    //     int new_push_index = start_index + 1;
    //     bool flag_empty = false;
    //     for (int i = 1; i < popV.size(); i++)
    //     {
    //         if (s.top() == popV[i])
    //             s.pop();
    //         else
    //         {
    //             if (flag_empty == true)
    //                 return false;
    //             for (int j = new_push_index; j < pushV.size(); j++)
    //             {
    //                 s.push(pushV[j]);
    //                 if (pushV[j] == popV[i])
    //                 {
    //                     s.pop();
    //                     new_push_index = j + 1;
    //                     if (new_push_index >= pushV.size())
    //                         flag_empty = true;
    //                     break;
    //                 }
    //                 if (j == pushV.size() - 1)
    //                     return false;
    //             }
    //         }
    //     }
    //     return true;
    // }
    bool IsPopOrder(vector<int> pushV, vector<int> popV)
    {
        if (pushV.size() == 0 || popV.size() == 0 || pushV.size() != popV.size())
            return false;
        
        stack<int> s;

        int p1 = -1;
        for (int p2 = 0; p2 < popV.size(); p2++)
        {
            //条件判断从前往后执行
            if (s.size()&&popV[p2] == s.top())
            {
                s.pop();
            }
            else
            {
                bool r = true;
                for (int i = p1 + 1; i < pushV.size(); i++)
                {
                    s.push(pushV[i]);
                    if (pushV[i] == popV[p2])
                    {
                        p1 = i;
                        r = false;
                        break;
                    }
                }
                if (r)
                    return false;
                s.pop();
            }
        }
        return true;
    }
};

int main()
{
    Solution solution;
    // int push_arry[5] = {1, 2, 3, 4, 5};
    // int pop_arry[5] = {4, 3, 5, 1, 2};
    // int pop_arry[5] = {4, 5, 3, 2, 1};

    // int push_arry[1] = {1};
    // int pop_arry[5] = {2};
    // vector<int> pushV = vector_init(push_arry, 5);
    // vector<int> popV = vector_init(pop_arry, 5);
    vector<int> pushV{1, 2, 3, 4, 5};
    vector<int> popV{4, 3, 5, 1, 2};

    bool is_right = solution.IsPopOrder(pushV, popV);
}