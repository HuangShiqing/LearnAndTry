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