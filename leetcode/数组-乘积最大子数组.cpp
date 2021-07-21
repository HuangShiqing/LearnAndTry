#include <iostream>
#include <vector>

using namespace std;

// 152. 乘积最大子数组
// 给你一个整数数组 nums ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

// 示例 1:
// 输入: [2,3,-2,4]
// 输出: 6
// 解释: 子数组 [2,3] 有最大乘积 6。

// 示例 2:
// 输入: [-2,0,-1]
// 输出: 0
// 解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。

// -------------------第二次刷-----------------------
// 2021年06月20日09:39:52
// 准备第一次社招
// 思路: 和最大和数组不一样, 因为是整数, 所以数值上来说乘的越多乘积和越大. 但是分了正负, 所以
// 每次得记录正的乘积和与负的乘积和

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