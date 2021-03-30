#include <numeric>
#include <vector>
using namespace std;

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
            if (find(used_index.begin(), used_index.end(), i) == used_index.end()) {
                used_index.push_back(i);
                result_v.push_back(nums[i]);
                permute_repeat(nums, used_index, result_vv, result_v);
                used_index.pop_back();
                result_v.pop_back();
            }
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result_vv;
        vector<int> result_v;
        vector<int> used_index;
        permute_repeat(nums, used_index, result_vv, result_v);
        return result_vv;
    }
};