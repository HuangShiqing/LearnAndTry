#include <vector>
using namespace std;


// 34. 在排序数组中查找元素的第一个和最后一个位置
// 给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
// 如果数组中不存在目标值 target，返回 [-1, -1]。
// 进阶：
// 你可以设计并实现时间复杂度为 O(log n) 的算法解决此问题吗？
 
// 示例 1：
// 输入：nums = [5,7,7,8,8,10], target = 8
// 输出：[3,4]

// 示例 2：
// 输入：nums = [5,7,7,8,8,10], target = 6
// 输出：[-1,-1]

// 示例 3：
// 输入：nums = [], target = 0
// 输出：[-1,-1]

// -------------------第二次刷-----------------------
// 2021年06月09日22:50:52
// 准备第一次社招
// 思路: 两次二分. nums[middle]==target后再判断. 

class Solution {
public:
    // 一次二分加左右遍历复杂度=logn+n=n
    // vector<int> searchRange(vector<int>& nums, int target) {
    //     vector<int> v = {-1, -1};
    //     int result = -1;
    //     int result_left, result_right;
    //     int left = 0;
    //     int right = nums.size() - 1;
    //     int middle = (left + right) / 2;

    //     while (left <= right) {
    //         if (target < nums[middle])
    //             right = middle - 1;
    //         else if (target > nums[middle])
    //             left = middle + 1;
    //         else {
    //             result = middle;
    //             break;
    //         }
    //         middle = (left + right) / 2;
    //     }
    //     if (result != -1) {
    //         result_left = result;
    //         result_right = result;
    //         while (result_left >= 0 && nums[result_left] == nums[result])
    //             result_left -= 1;
    //         while (result_right < nums.size() && nums[result_right] == nums[result])
    //             result_right += 1;
    //         result_left += 1;
    //         result_right -= 1;
    //         v[0] = result_left;
    //         v[1] = result_right;
    //         return v;
    //     } else
    //         return v;
    // }

    // 两次二分,复杂度logn
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> v = {-1, -1};
        int result_left = -1, result_right = -1;
        int left = 0;
        int right = nums.size() - 1;
        int middle = (left + right) / 2;
        while (left <= right) {
            if (target < nums[middle])
                right = middle - 1;
            else if (target > nums[middle])
                left = middle + 1;
            else if (target == nums[middle]) {
                if (middle - 1 >= 0) {
                    if (target != nums[middle - 1]) {
                        result_left = middle;
                        break;
                    } else {
                        right = middle - 1;
                    }
                } else {
                    result_left = middle;
                    break;
                }
            }
            middle = (left + right) / 2;
        }

        left = 0;
        right = nums.size() - 1;
        middle = (left + right) / 2;
        while (left <= right) {
            if (target < nums[middle])
                right = middle - 1;
            else if (target > nums[middle])
                left = middle + 1;
            else if (target == nums[middle]) {
                if (middle + 1 < nums.size()) {
                    if (target != nums[middle + 1]) {
                        result_right = middle;
                        break;
                    } else {
                        left = middle + 1;
                    }
                } else {
                    result_right = middle;
                    break;
                }
            }
            middle = (left + right) / 2;
        }

        if (result_left != -1 && result_right != -1) {
            v[0] = result_left;
            v[1] = result_right;
            return v;
        } else
            return v;
    }
};