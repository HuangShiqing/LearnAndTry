#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int imax = INT32_MIN;
        int p_max = 1;
        int n_min = 1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] < 0)
                swap(p_max, n_min);
            p_max = max(p_max * nums[i], nums[i]);
            n_min = min(n_min * nums[i], nums[i]);

            imax = max(imax, p_max);
        }
        return imax;
    }
};