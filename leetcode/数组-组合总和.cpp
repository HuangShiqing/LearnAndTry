#include <numeric>
#include <vector>
using namespace std;

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