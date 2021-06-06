// 剑指 Offer 57. 和为s的两个数字
// 输入一个递增排序的数组和一个数字s，在数组中查找两个数，使得它们的和正好是s。如果有多对数字的和等于s，则输出任意一对即可。

// 示例 1：
// 输入：nums = [2,7,11,15], target = 9
// 输出：[2,7] 或者 [7,2]

// 示例 2：
// 输入：nums = [10,26,30,31,47,60], target = 40
// 输出：[10,30] 或者 [30,10]

// -------------------第三次刷-----------------------
// 2021年6月2日15:17:03
// 准备第一次社招
// 思路: 很简单, 双指针, 向中间靠拢
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size()-1;
        vector<int> r;
        while(left<=right){
            int sum = nums[left]+nums[right];
            if(sum==target){
                r.push_back(nums[left]);
                r.push_back(nums[right]);
                break;
            }
            else if(sum<target){
                left++;
            }
            else{
                right--;
            }
        }

        return r;
    }
};


//page:280
#include <vector>
#include <iostream>
using namespace std;

class Solution
{
public:
    // vector<int> FindNumbersWithSum(vector<int> array, int sum)
    // {
    //     // if
    //     int start = 0;
    //     int end = array.size() - 1;
    //     vector<vector<int>> result;
    //     while (start < end)
    //     {
    //         int sum_temp = array[start] + array[end];
    //         if (sum_temp == sum)
    //         {
    //             vector<int> result_temp{array[start], array[end]};
    //             result.push_back(result_temp);
    //             end--;
    //         }
    //         else if (sum_temp < sum)
    //         {
    //             start++;
    //         }
    //         else
    //         {
    //             end--;
    //         }
    //     }

    //     int min_mul = INT32_MAX;
    //     vector<int> vresult;
    //     for (int i = 0; i < result.size(); i++)
    //     {
    //         if (result[i][0] * result[i][1] < min_mul)
    //         {
    //             min_mul = result[i][0] * result[i][1];
    //             vresult = result[i];
    //         }
    //     }
    //     return vresult;
    // }
    vector<int> FindNumbersWithSum(vector<int> array, int sum)
    {
        vector<vector<int>> vv;
        vector<int> v;
        if (array.size() <= 1)
            return v;
        int p1 = 0;
        int p2 = array.size() - 1;

        while (p1 < p2)
        {
            if (array[p1] + array[p2] < sum)
                p1++;
            else if (array[p1] + array[p2] > sum)
                p2--;
            else
            {
                v.push_back(array[p1]);
                v.push_back(array[p2]);
                vv.push_back(v);
                v.clear();
                p2--;
            }
        }

        if(vv.size()==0)
            return v;

        int min = INT32_MAX;
        int min_index = 0;
        for (int i = 0; i < vv.size(); i++)
        {
            if (vv[i][0] * vv[i][1] < min)
            {
                min = vv[i][0] * vv[i][1];
                min_index = i;
            }
        }

        return vv[min_index];
    }
};

int main()
{
    Solution solution;
    // vector<int> vdata{1, 2, 4, 7, 11, 15};
    // int sum = 15;
    vector<int> vdata{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int sum = 21;
    solution.FindNumbersWithSum(vdata, sum);
}