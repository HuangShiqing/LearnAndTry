#include <vector>
#include <stack>
using namespace std;

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