// 剑指 Offer 10- II. 青蛙跳台阶问题
// 一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。
// 答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
// 示例 1：
// 输入：n = 2
// 输出：2
// 示例 2：
// 输入：n = 7
// 输出：21
// 示例 3：
// 输入：n = 0
// 输出：1

// 2021年04月25日22:41:25
// 准备第一次社招
// 思路:
// 最简单的动态规划, 不需要解释
#include <vector>
using namespace std;

class Solution {
public:
    int numWays(int n) {
        if (n == 0)
            return 1;
        else if (n == 1)
            return 1;

        vector<int> dp(n + 1);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = (dp[i - 1] + dp[i - 2]) % (int)(1e9 + 7);
        }
        return dp[n];
    }
};