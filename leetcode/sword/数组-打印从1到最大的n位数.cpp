// 剑指 Offer 17. 打印从1到最大的n位数
// 输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。

// 示例 1:
// 输入: n = 1
// 输出: [1,2,3,4,5,6,7,8,9]
 
// 说明：
// 用返回一个整数列表来代替打印
// n 为正整数


// -------------------第三次刷-----------------------
// 2021年5月11日14:52:37
// 准备第一次社招
// 思路: 什么鬼. for循环就好了, 而且本来应该考虑的大数问题也因为返回类型是int而限定了

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> printNumbers(int n) {
        vector<int> r;
        int t = 1;
        for(int i=0;i<n;i++)
            t*=10;

        for(int i=1;i<t;i++)
            r.push_back(i);
        return r;
    }
};