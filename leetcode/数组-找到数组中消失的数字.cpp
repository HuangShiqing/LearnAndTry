#include <iostream>
#include <vector>
using namespace std;

// 448. 找到所有数组中消失的数字
// 给你一个含 n 个整数的数组 nums ，其中 nums[i] 在区间 [1, n] 内。请你找出所有在 [1, n] 范围内但没有出现在 nums 中的数字，并以数组的形式返回结果。

// 示例 1：
// 输入：nums = [4,3,2,7,8,2,3,1]
// 输出：[5,6]

// 示例 2：
// 输入：nums = [1,1]
// 输出：[2]

// -------------------第二次刷-----------------------
// 2021年7月19日10:33:00
// 准备第一次社招
// 思路:
// 将数组元素对应为索引的位置加n
// 遍历加n后的数组，若数组元素值小于等于n，则说明数组下标值不存在，即消失的数字

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> res;
        if (nums.empty())
            return nums;
        for (int i = 0; i < nums.size(); i++) {
            int index = (nums[i] - 1) % nums.size();  //-1是因为数组元素范围是1-n,后面push的时候会+1恢复.
                                                      // 取余是因为出现两次的数可能之前已经加过了
            nums[index] += nums.size();
        }
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] <= nums.size())
                res.push_back(i + 1);
        }
        return res;
    }
};