#include <vector>
using namespace std;

// 581. 最短无序连续子数组
// 给你一个整数数组 nums ，你需要找出一个 连续子数组 ，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。
// 请你找出符合题意的 最短 子数组，并输出它的长度。

// 示例 1：
// 输入：nums = [2,6,4,8,10,9,15]
// 输出：5
// 解释：你只需要对 [6, 4, 8, 10, 9] 进行升序排序，那么整个表都会变为升序排序。

// 示例 2：
// 输入：nums = [1,2,3,4]
// 输出：0

// 示例 3：
// 输入：nums = [1]
// 输出：0

// -------------------第二次刷-----------------------
// 2021年7月20日10:53:04
// 准备第一次社招
// 思路: 
//从左往右遍历, 找到第一个不正常的降序的两个连续元素nums[i]>nums[i+1], 然后从i开始往右继续遍历找到最小的数min
//从右往左遍历, 找到第一个不正常的降序的两个连续元素nums[i-1]>nums[i], 然后从i-1开始往左继续在乱序的数组里遍历找到最大的数max
//两个异常之间肯定是乱序数组, 但是把这个乱序数组原地恢复后就一定能保证两个连接处是正常的么? 因此需要找到乱序数组里的min和max
//然后重新从左往右遍历, 找到min和max正常排序应该在的位置, 即找到从左往右第一个大于min的数min_right和从右往左第一个小于max的数max_left, 
// 正常排序的时候min和max之间(包括这两者)组成的数组即为最短乱序数组

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        bool flag = false;
        int mins = INT32_MAX;
        for(int i =0; i<nums.size()-1;i++){
            if(nums[i]>nums[i+1]){
                flag=true;
                mins = min(mins, min(nums[i], nums[i+1]));
            }
                
            if(flag==true)
                mins = min(mins, nums[i]);
        }

        flag = false;
        int maxs = INT32_MIN;
        for(int i =nums.size()-2; i>=0;i--){
            if(nums[i+1]<nums[i]){
                flag=true;
                maxs = max(maxs, max(nums[i], nums[i+1]));
            }
                
            if(flag==true)
                maxs = max(maxs, nums[i]);
        }

        int min_right;
        for(min_right=0;min_right<nums.size();min_right++)
        {
            if(nums[min_right]>mins)
                break;
        }

        int max_left;
        for(max_left=nums.size()-1;max_left>=0;max_left--)
        {
            if(nums[max_left]<maxs)
                break;
        }
        return min_right>max_left?0:max_left-min_right+1;
    }
};