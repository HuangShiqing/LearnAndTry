#include <vector>
using namespace std;

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