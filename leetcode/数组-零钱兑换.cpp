#include <iostream>
#include <vector>
using namespace std;


// 322. 零钱兑换
// 给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。
// 你可以认为每种硬币的数量是无限的。

// 示例 1：
// 输入：coins = [1, 2, 5], amount = 11
// 输出：3 
// 解释：11 = 5 + 5 + 1

// 示例 2：
// 输入：coins = [2], amount = 3
// 输出：-1

// 示例 3：
// 输入：coins = [1], amount = 0
// 输出：0

// 示例 4：
// 输入：coins = [1], amount = 1
// 输出：1

// 示例 5：
// 输入：coins = [1], amount = 2
// 输出：2

// -------------------第二次刷-----------------------
// 2021年7月5日10:20:08
// 准备第一次社招
// 思路:
// dp[i]代表凑成总金额i最少的硬币个数
// dp[i+k] = min(dp[i]+1, dp[i+k]), k为不同金额的硬币
// dp[0] = 0

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, -1);
        dp[0] = 0;

        for (int i = 0; i <= amount; i++) {
            if (dp[i] == -1)
                continue;
            for (auto k : coins) {
                if ((long long)i + (long long)k <= (long long)amount)//signed integer overflow
                    if (dp[i + k] == -1)
                        dp[i + k] = dp[i] + 1;
                    else
                        dp[i + k] = min(dp[i] + 1, dp[i + k]);
            }
        }
        return dp[amount];
    }
};