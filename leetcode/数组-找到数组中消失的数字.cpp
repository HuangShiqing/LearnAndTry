#include <iostream>
#include <vector>
using namespace std;

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