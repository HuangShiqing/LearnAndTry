// 494. 目标和
// 给你一个整数数组 nums 和一个整数 target 。
// 向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：
// 例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1" 。
// 返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目。

// 示例 1：
// 输入：nums = [1,1,1,1,1], target = 3
// 输出：5
// 解释：一共有 5 种方法让最终目标和为 3 。
// -1 + 1 + 1 + 1 + 1 = 3
// +1 - 1 + 1 + 1 + 1 = 3
// +1 + 1 - 1 + 1 + 1 = 3
// +1 + 1 + 1 - 1 + 1 = 3
// +1 + 1 + 1 + 1 - 1 = 3

// 示例 2：
// 输入：nums = [1], target = 1
// 输出：1

// -------------------第二次刷-----------------------
// 2021年7月19日10:33:00
// 准备第一次社招
// 思路: 简单的回溯即可

#include <vector>
using namespace std;

class Solution {
public:
    int count=0;
    void dfs(vector<int>& nums, int target, int sum, int index){
        if(index==nums.size()){
            if(sum==target)//必须要到终点才能看是否满足+1条件
                count++;
            return;
        }
            
        dfs(nums, target, sum+nums[index], index+1);
        dfs(nums, target, sum-nums[index], index+1);
    }

    int findTargetSumWays(vector<int>& nums, int target) {
        if(nums.size()==0)
            return 0;

        dfs(nums, target, 0, 0);
        return count;
    }
};