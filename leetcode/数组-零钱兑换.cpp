#include <iostream>
#include <vector>
using namespace std;

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