// 剑指 Offer 42. 连续子数组的最大和
// 输入一个整型数组，数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。

// 要求时间复杂度为O(n)。

// 示例1:
// 输入: nums = [-2,1,-3,4,-1,2,1,-5,4]
// 输出: 6
// 解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。

// -------------------第三次刷-----------------------
// 2021年5月18日14:31:58
// 准备第一次社招
// 思路: 蛮简单的, 思路看代码就成. 就是到底是先判断小于0还是先加的问题, 应该先判断. 因为默认执行+=, 但是如果执行前sum已经小于0了, 就
// 可以抛弃那部分小于0的sum重新对sum赋值即可

#include <vector>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = 0;
        int max_sum = INT32_MIN;
        for(int i=0;i<nums.size();i++){
            if(sum<0)
                sum=nums[i];
            else
                sum+=nums[i];

            if(sum>max_sum)
                max_sum = sum;
        }
        return max_sum;
    }
};


//page 218
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    // int FindGreatestSumOfSubArray(vector<int> array) {
    //     if(array.size()==0)
    //         return 0;

    //     int nGreatestSum = -1;
    //     int nCurSum = 0;
    //     for(int i =0;i<array.size();i++)
    //     {
    //         if(nCurSum<0)
    //             nCurSum = array[i];
    //         else
    //             nCurSum += array[i];

    //         if(nCurSum>nGreatestSum)
    //             nGreatestSum = nCurSum;
    //     }
    //     return nGreatestSum;
    // }
    int FindGreatestSumOfSubArray(vector<int> array)
    {
        if (array.size() == 0)
            return 0;

        int sum = 0;
        int great_sum = INT32_MIN;
        for (int i = 0; i < array.size(); i++)
        {            
            
            if (sum < 0)
                sum = array[i];
            else
                sum += array[i];

            if (sum > great_sum)
                great_sum = sum;
        }
        return great_sum;
    }
};

int main()
{
    Solution solution;
    vector<int> array{1, -2, 3, 10, -4, 7, 2, -5};

    int result = solution.FindGreatestSumOfSubArray(array);
}