#include <iostream>
#include <vector>
using namespace std;

// numSquares(n)=min(numSquares(n-k) + 1)  ∀k∈square numbers


// 279. 完全平方数
// 给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。
// 给你一个整数 n ，返回和为 n 的完全平方数的 最少数量 。
// 完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。

// 示例 1：
// 输入：n = 12
// 输出：3 
// 解释：12 = 4 + 4 + 4

// 示例 2：
// 输入：n = 13
// 输出：2
// 解释：13 = 4 + 9

// -------------------第二次刷-----------------------
// 2021年07月02日00:05:03
// 准备第一次社招
// 思路: 动态规划. dp[i]表示结果. dp[i] = min(dp[i-j*j])+1, 其中j是从0遍历到根号i找到的使dp[i-j*j]最小
class Solution {
public:
    int numSquares(int n) {
        vector<int> f(n + 1);
        for (int i = 1; i <= n; i++) {
            int minn = INT_MAX;
            for (int j = 1; j * j <= i; j++) {
                minn = min(minn, f[i - j * j]);
            }
            f[i] = minn + 1;
        }
        return f[n];
    }
};