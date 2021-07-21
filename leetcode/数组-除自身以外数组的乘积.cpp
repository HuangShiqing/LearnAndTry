#include <iostream>
#include <vector>
using namespace std;

// 题目:除自身以外数组的乘积
// 给你一个长度为 n 的整数数组 nums，其中 n > 1，返回输出数组 output ，其中
// output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。 示例: 输入: [1,2,3,4] 输出: [24,12,8,6]
// 提示：题目数据保证数组之中任意元素的全部前缀元素和后缀（甚至是整个数组）的乘积都在 32 位整数范围内。
// 说明: 请不要使用除法，且在 O(n) 时间复杂度内完成此题。

// -------------------第二次刷-----------------------
// 2021年6月30日15:03:58
// 准备第一次社招
// 思路:利用索引左侧所有数字的乘积和右侧所有数字的乘积（即前缀与后缀）相乘得到答案
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> left(nums.size(), 1);
        vector<int> right(nums.size(), 1);
        vector<int> r(nums.size(), 1);

        // left[i]是该元素左边所有元素的乘积
        for (int i = 1; i < nums.size(); i++) {
            left[i] = left[i - 1] * nums[i - 1];
        }
        for (int i = nums.size() - 2; i >= 0; i--) {
            right[i] = right[i + 1] * nums[i + 1];
        }

        for (int i = 0; i < nums.size(); i++) {
            r[i] = left[i] * right[i];
        }
        return r;
    }
};