// dp[i] 表示：以 nums[i] 结尾 的「上升子序列」的长度
// dp[i]= max(dp[j])+1, 其中0≤j<i,nums[j]<nums[i]
// dp[i] = 1，11 个字符显然是长度为 11 的上升子序列。
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
        }

        int num = INT32_MIN;
        for (int i = 0; i < dp.size(); i++)
            num = max(num, dp[i]);
        return num;
    }
};
