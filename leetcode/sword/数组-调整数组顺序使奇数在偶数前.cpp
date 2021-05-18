// 剑指 Offer 21. 调整数组顺序使奇数位于偶数前面
// 输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数位于数组的前半部分，所有偶数位于数组的后半部分。

// 示例：
// 输入：nums = [1,2,3,4]
// 输出：[1,3,2,4] 
// 注：[3,1,2,4] 也是正确的答案之一。
 
// 提示：
// 0 <= nums.length <= 50000
// 1 <= nums[i] <= 10000

// -------------------第三次刷-----------------------
// 2021年5月12日11:38:45
// 准备第一次社招
// 思路: 头尾双指针呗 很简单, 退出条件是头指针大于尾指针
// 注意: 移动指针的时候需要判断是否头指针大于尾指针, 移动完成后仍然需要判断是否头指针大于尾指针

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        vector<int> v(nums.begin(), nums.end());
        if(nums.size() == 0)
            return v;

        int index_start = 0;
        int index_end = nums.size() - 1;

        while(index_start<index_end){
            while(v[index_start]%2==1&&index_start<index_end)
                index_start++;
            while(v[index_end]%2==0&&index_start<index_end)
                index_end--;
            if(index_start>=index_end)
                return v;
            
            swap(v[index_start], v[index_end]);
        }
        return v;
    }
};

//page 129
#include <iostream>
#include <vector>
using namespace std;

// 需要保证稳定性，冒泡法，时间复杂度为n2
void reOrderArray(vector<int> &array)
{
    if(array.size()==0)
        return;
    for(int i=0;i<array.size()-1;i++)
    {
        // -i是因为和冒泡一样，要排到后面的数每次都会被弄到最后，所以数组后面的是有序的
        for(int j=0;j<array.size()-1-i;j++)
        {
            if(array[j]%2==0&&array[j+1]%2==1)
                swap(array[j],array[j+1]);
        }
    }
}

// 不考虑稳定性
// 可以用头尾指针，只需要遍历一遍，时间复杂度为n
void reOrderArray_2(vector<int> &array)
{
    if(array.size()==0)
        return;
    
    int index_begain = 0;
    int index_end = array.size()-1;

    // 直到两个指针相遇
    while(index_begain<index_end)
    {
        // 让头指针指向要在后的偶数
        while(array[index_begain]%2!=0&&index_begain<index_end)
            index_begain++;
        
        // 让头指针指向要在后的偶数
        while(array[index_end]%2==0&&index_begain<index_end)
            index_end--;
        
        if(index_begain<index_end)
            swap(array[index_begain],array[index_end]);

    return 0;
}