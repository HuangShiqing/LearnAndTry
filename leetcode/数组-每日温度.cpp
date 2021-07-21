#include <vector>
#include <stack>
using namespace std;

// 739. 每日温度
// 请根据每日 气温 列表 temperatures ，请计算在每一天需要等几天才会有更高的温度。如果气温在这之后都不会升高，请在该位置用 0 来代替。

// 示例 1:
// 输入: temperatures = [73,74,75,71,69,72,76,73]
// 输出: [1,1,4,2,1,1,0,0]

// 示例 2:
// 输入: temperatures = [30,40,50,60]
// 输出: [1,1,1,0]

// 示例 3:
// 输入: temperatures = [30,60,90]
// 输出: [1,1,0]

// -------------------第二次刷-----------------------
// 2021年7月21日15:49:27
// 准备第一次社招
// 思路:
// 单调栈
// 想要找一个递增的, 那就设置一个单调递减栈, 在异常pop的时候进行处理.
// 以index入栈, 递减的情况把index都入栈, 直到找到异常(非递减), 逐一弹出index, 
// 每个r[index]都等于i-index

class Solution {
public:

    vector<int> dailyTemperatures(vector<int>& T) {
        vector<int> r(T.size());
        stack<int> s;
        for(int i=0;i<T.size();i++){
            while(!s.empty() && T[s.top()] < T[i] ){
                int preIndex = s.top();
                r[preIndex] = i-preIndex;
                s.pop();
            }
            s.push(i);
        }
        return r;
    }
};