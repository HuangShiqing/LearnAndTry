#include <iostream>
#include <vector>
using namespace std;

// 用 f[i] 表示第 i 天结束之后的「累计最大收益」
// 1. 我们目前持有一支股票，对应的「累计最大收益」记为 f[i][0]
// 2. 我们目前不持有任何股票，并且处于冷冻期中(第i+1天不能买)，对应的「累计最大收益」记为 f[i][1]
// 3. 我们目前不持有任何股票，并且不处于冷冻期中(第i+1天能买)，对应的「累计最大收益」记为 f[i][2]

// 对于 f[i][0] ，
// 1.我们目前持有的这一支股票可以是在第 i - 1 天就已经持有的，对应的状态为 f[i - 1][0] ；
// 2.或者是第 i 天买入的，那么第 i - 1 天就不能持有股票并且不处于冷冻期中，对应的状态为 f[i - 1][2] 加上买入股票的负收益
// prices[i]
// f[i][0]=max(f[i−1][0],f[i−1][2]−prices[i])

// 对于 f[i][1]，
// 我们在第 i 天结束之后处于冷冻期的原因是在当天卖出了股票，那么说明在第 i-1 天时我们必须持有一支股票，对应的状态为
// f[i-1][0] 加上卖出股票的正收益 prices[i]
// f[i][1]=f[i−1][0]+prices[i]

// 对于 f[i][2]，
// 我们在第 i 天结束之后不持有任何股票并且不处于冷冻期, 说明当天没有进行任何操作，即第 i-1 天时不持有任何股票,
// 如果第 i-1 天处于冷冻期，对应的状态为 f[i-1][1], 如果不处于冷冻期，对应的状态为 f[i-1][2]
// f[i][2]=max(f[i−1][1],f[i−1][2])

// 第零天
// f[0][0]=−prices[0]
// f[0][1]=0
// f[0][2]=0

// 结果  = max(f[n][0],f[n][1],f[n][2])

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(3));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        dp[0][2] = 0;
        for (int i = 1; i < n; ++i) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][2] - prices[i]);
            dp[i][1] = dp[i - 1][0] + prices[i];
            dp[i][2] = max(dp[i - 1][1], dp[i - 1][2]);
        }
        return max(dp[n-1][0], dp[n-1][1], dp[n-1][2]);
    }
};