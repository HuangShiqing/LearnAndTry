#include <numeric>
#include <vector>
using namespace std;

// 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
// 示例 1：
// 输入：nums = [1,2,3]
// 输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

// 示例 2：
// 输入：nums = [0,1]
// 输出：[[0,1],[1,0]]

// 示例 3：
// 输入：nums = [1]
// 输出：[[1]]

// -------------------第二次刷-----------------------
// 2021年06月09日22:50:52
// 准备第一次社招
// 思路: 回溯遍历, 因为不能重复, 所以用used_index来保存

class Solution {
public:
    void permute_repeat(vector<int>& nums, vector<int>& used_index, vector<vector<int>>& result_vv,
                        vector<int>& result_v) {
        if (used_index.size() == nums.size()) {
            result_vv.push_back(result_v);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            // 要求选取不能重复可以用一个used_index,要求组合不能重复则可以用一个index然后循环要从new_index要>=old_index
            // if (find(used_index.begin(), used_index.end(), i) == used_index.end()) {
            if(used_index[i] == 0){
                // used_index.push_back(i);
                used_index[i] = 1;
                result_v.push_back(nums[i]);
                permute_repeat(nums, used_index, result_vv, result_v);
                // used_index.pop_back();
                used_index[i] = 0;
                result_v.pop_back();
            }
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result_vv;
        vector<int> result_v;
        vector<int> used_index(nums.size(), 0);
        permute_repeat(nums, used_index, result_vv, result_v);
        return result_vv;
    }
};