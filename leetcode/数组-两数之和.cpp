// 1. 两数之和
// 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
// 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
// 你可以按任意顺序返回答案。

// 示例 1：
// 输入：nums = [2,7,11,15], target = 9
// 输出：[0,1]
// 解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。

// 示例 2：
// 输入：nums = [3,2,4], target = 6
// 输出：[1,2]

// 示例 3：
// 输入：nums = [3,3], target = 6
// 输出：[0,1]

// -------------------第二次刷-----------------------
// 2021年06月06日20:50:26
// 准备第一次社招
// 思路一: 哈希表, 遍历一遍建立值和索引的map，然后再遍历并从map中找是否有差值. 时间复杂度为O(N), 查表时间为O(1)

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        vector<int> v;
        for(int i=0;i<nums.size();i++)
        {
            map[nums[i]] = i;
        }

        for(int i=0;i<nums.size();i++)
        {
            int another = target - nums[i];
            if (map.find(another) == map.end())
                ;
            else
            {
                //需要判断不能是同一个数用两遍
                if(i == map[another])
                    continue;
                v.push_back(i);
                v.push_back(map[another]);
                break;
            }
                
        }
        return v;
        
    }
};

//思路二: 排序, 然后头尾双指针, 时间复杂度O(NlogN)