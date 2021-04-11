#include <iostream>
#include <vector>
using namespace std;

// 使用双指针，左指针指向当前已经处理好的序列的后一个，即指向当前要处理的0,
// 右指针从左指针开始向后遍历,指向要交换的非0

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int left = 0;
        int right = 0;

        while (1) {
            while (nums[left] != 0) {
                left++;
                if (left >= nums.size())
                    return;
            }
            right = left;
            while (nums[right] == 0) {
                right++;
                if (right >= nums.size())
                    return;
            }
            swap(nums[left], nums[right]);
        }
    }
};