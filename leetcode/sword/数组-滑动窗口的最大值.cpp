// 剑指 Offer 59 - I. 滑动窗口的最大值
// 给定一个数组 nums 和滑动窗口的大小 k，请找出所有滑动窗口里的最大值。

// 示例:
// 输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
// 输出: [3,3,5,5,6,7] 
// 解释: 

//   滑动窗口的位置                最大值
// ---------------               -----
// [1  3  -1] -3  5  3  6  7       3
//  1 [3  -1  -3] 5  3  6  7       3
//  1  3 [-1  -3  5] 3  6  7       5
//  1  3  -1 [-3  5  3] 6  7       5
//  1  3  -1  -3 [5  3  6] 7       6
//  1  3  -1  -3  5 [3  6  7]      7

// 提示：
// 你可以假设 k 总是有效的，在输入数组不为空的情况下，1 ≤ k ≤ 输入数组的大小。

// -------------------第三次刷-----------------------
// 2021年6月3日14:30:29
// 准备第一次社招
// 思路:

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {

    }
};

#include <vector>
#include <iostream>
using namespace std;

class Solution
{
public:
    vector<int> maxInWindows(const vector<int> &num, unsigned int size)
    {
        vector<int> v;
        if (size > num.size() || size == 0)
            return v;

        int left = 0;
        int right = size - 1;

        while (right <= num.size() - 1)
        {
            int temp_max = INT32_MIN;
            for (int i = left; i <= right; i++)
            {
                if (num[i] > temp_max)
                    temp_max = num[i];
            }
            v.push_back(temp_max);
            left++;
            right++;
        }
        return v;
    }
}; 
