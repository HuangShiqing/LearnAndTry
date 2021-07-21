#include <iostream>
#include <vector>
using namespace std;

// 283. 移动零
// 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

// 示例:
// 输入: [0,1,0,3,12]
// 输出: [1,3,12,0,0]
// 说明:
// 必须在原数组上操作，不能拷贝额外的数组。
// 尽量减少操作次数。

// -------------------第二次刷-----------------------
// 2021年7月2日10:59:10
// 准备第一次社招
// 思路1: 不用交换. 快慢双指针. fast只管往前遍历, slow只有在fast遇到非0值时才nums[slow]=nums[fast], 然后slow+=1. 
// fast到头后就继续把slow后面的都赋值成0

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int fast = 0;
        int slow = 0;
        while(fast<nums.size()){
            if(nums[fast]!=0){
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }

        while(slow<nums.size()){
            nums[slow] = 0;
            slow++;
        }
        return;
    }
};

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