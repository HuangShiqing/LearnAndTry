#include <iostream>
#include <vector>
using namespace std;

// 416. 分割等和子集
// 给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

// 示例 1：
// 输入：nums = [1,5,11,5]
// 输出：true
// 解释：数组可以分割成 [1, 5, 5] 和 [11] 。

// 示例 2：
// 输入：nums = [1,2,3,5]
// 输出：false
// 解释：数组不能分割成两个元素和相等的子集。

// -------------------第二次刷-----------------------
// 2021年7月15日10:20:46
// 准备第一次社招
// 思路:

//动态规划
//令dp[i][j]代表数组nums[0:i]是否存在部分数的和为j, 注意是部分数的和而不是说全部数的和
//要返回的结果就是dp[nums.size()-1][sum(nums)/2]

// 只要nums[0]不大于target=sum(nums)/2, 初始dp[0][nums[0]] = true, 如果大于了函数可以直接返回false了
// 三种情况为true:
// 1.如果新增数nums[i]就等于和数j, 那么肯定能组成部分和为j. 即如果nums[i]==j, 则dp[i][j]=true
// 2.如果未新增数nums[i]时就已经可以组成部分和为j, 则新增数nums[i]也肯定能组成. 即如果dp[i-1][j]==true, 则dp[i][j]=true
// 3.如果未新增数nums[i]时可以组成部分和j-nums[i], 那新增数nums[i]后刚好能够组成部分和j. 即如果dp[i-1][j-nums[i]]=true, 则dp[i][j]=true

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num : nums)
            sum += num;
        if (sum % 2 != 0)
            return false;
        int target = sum / 2;

        vector<vector<bool>> dp(nums.size(), vector<bool>(target+1, false));

        if (nums[0] <= target)
            dp[0][nums[0]] = true;

        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j <= target; j++) {
                dp[i][j] = dp[i - 1][j];

                if (nums[i] == j) {
                    dp[i][j] = true;
                    continue;
                }
                if (nums[i] < j) {
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i]];
                }
            }
        }
        return dp[nums.size() - 1][target];
    }
};