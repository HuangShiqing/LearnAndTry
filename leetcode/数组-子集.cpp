#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 78. 子集
// 给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。
// 解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

// 示例 1：
// 输入：nums = [1,2,3]
// 输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

// 示例 2：
// 输入：nums = [0]
// 输出：[[],[0]]

// -------------------第二次刷-----------------------
// 2021年6月11日10:46:00
// 准备第一次社招
// 思路: 就递归遍历呗, 每次处理就两种情况, 放还是不放
class Solution {
public:
    void subsets_repeat(vector<vector<int>>& result, vector<int>& result_tmp, vector<int>& nums, int index) {
        if (index == nums.size()) {//该push的时候应该是index超出范围
            result.push_back(result_tmp);
            return;
        }

        // 就两种情况,把当前index对应的元素放或者不放到result_tmp里
        result_tmp.push_back(nums[index]);
        subsets_repeat(result, result_tmp, nums, index + 1);
        result_tmp.pop_back();

        subsets_repeat(result, result_tmp, nums, index + 1);
    };

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> result_tmp;
        subsets_repeat(result, result_tmp, nums, 0);
        return result;
    }
};