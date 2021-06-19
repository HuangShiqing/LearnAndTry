#include <numeric>
#include <vector>
using namespace std;

// 39. 组合总和
// 给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
// candidates 中的数字可以无限制重复被选取。

// 说明：
// 所有数字（包括 target）都是正整数。
// 解集不能包含重复的组合。 

// 示例 1：
// 输入：candidates = [2,3,6,7], target = 7,
// 所求解集为：
// [
//   [7],
//   [2,2,3]
// ]

// 示例 2：
// 输入：candidates = [2,3,5], target = 8,
// 所求解集为：
// [
//   [2,2,2,2],
//   [2,3,3],
//   [3,5]
// ]

// -------------------第二次刷-----------------------
// 2021年06月09日22:50:52
// 准备第一次社招
// 思路: 求每种组合时, 设定一个distant, 然后多次遍历, 因为数字可重复, 所以每次遍历范围都是从头到尾. 

class Solution {
public:
    void combinationSum_repeat(vector<int>& candidates, int target, int distance, int index,
                               vector<vector<int>>& result_vv, vector<int>& result_v) {
        if (distance == 0) {
            result_vv.push_back(result_v);
            return;
        }

        for (int i = index; i < candidates.size(); i++) {
            if (candidates[i] <= distance) {
                result_v.push_back(candidates[i]);
                combinationSum_repeat(candidates, target, distance - candidates[i], i, result_vv, result_v);
                result_v.pop_back();
            } else
                continue;
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result_vv;
        vector<int> result_v;
        combinationSum_repeat(candidates, target, target, 0, result_vv, result_v);
        return result_vv;
    }
};