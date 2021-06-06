// 剑指 Offer 53 - II. 0～n-1中缺失的数字
// 一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0～n-1之内。在范围0～n-1内的n个数字中有且只有一个数字不在该数组中，请找出这个数字。

// 示例 1:
// 输入: [0,1,3]
// 输出: 2

// 示例 2:
// 输入: [0,1,2,3,4,5,6,7,9]
// 输出: 8

// -------------------第三次刷-----------------------
// 2021年6月1日10:04:34
// 准备第一次社招
// 思路: 
// 索引:[0,1,2]
// 数组:[0,1,3]
// 缺失的数就是第一个索引与数组对不上的索引值. 即二分的时候找的是nums[middle]!=middle, 且nums[middle-1]==middle-1.
// 注意: 考虑两端
// 缺失0, 考虑数组越界时已覆盖
// 索引:[0,1,2]
// 数组:[1,2,3]
// 缺失3, 则出现二分找不到的现象, 由于题目是一定会有缺失的数字, 则r=-1时, 直接返回num.size()即可
// 索引:[0,1,2]
// 数组:[0,1,2]


#include <vector>
using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        int middle = (left+right)/2;
        int r= -1;
        while(left<=right){
            if(nums[middle]==middle){
                left=middle+1;
            }
            else{
                if(middle==0){
                    return middle;
                }
                else{
                    if(nums[middle-1]==middle-1)
                        return middle;
                    else
                        right=middle-1;
                }
            }

            middle = (left+right)/2;
        }
        return nums.size();
    }
};