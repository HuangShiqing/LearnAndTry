#include <iostream>
#include <vector>
using namespace std;

// 300. 最长递增子序列
// 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
// 子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。

// 示例 1：
// 输入：nums = [10,9,2,5,3,7,101,18]
// 输出：4
// 解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。

// 示例 2：
// 输入：nums = [0,1,0,3,2,3]
// 输出：4

// 示例 3：
// 输入：nums = [7,7,7,7,7,7,7]
// 输出：1

// -------------------第二次刷-----------------------
// 2021年7月2日10:59:10
// 准备第一次社招
// 思路: 动态规划, dp[i]代表要求的结果. 状态转移就是dp[i] = max(dp[i], dp[j]+1); 遍历i前面的dp[j]找到满足nums[j]<nums[i]中最大的dp[j], 
// 要用max的原因是因为不一定, 所有小于nums[i]的nums[j]都是"那条序列"里的. 

// 类似的还有另外一题是求最长"连续"序列, 使用一个map来记录数和其所在序列的长度, 处理nums[i]时
// 找nums[i]-1和nums[i]+1是否在map里

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j]+1);
            }
        }
        int num=INT32_MIN;
        for(int i=0;i<dp.size();i++)
            num = max(num, dp[i]);
        return num;
    }
};