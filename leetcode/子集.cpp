#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

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