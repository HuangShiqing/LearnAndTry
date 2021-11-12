// 15. 三数之和
// 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有和为 0 且不重复的三元组。
// 注意：答案中不可以包含重复的三元组。
// 示例 1：
// 输入：nums = [-1,0,1,2,-1,-4]
// 输出：[[-1,-1,2],[-1,0,1]]

// 示例 2：
// 输入：nums = []
// 输出：[]

// 示例 3：
// 输入：nums = [0]
// 输出：[]

// -------------------第二次刷-----------------------
// 2021年6月8日14:58:36
// 准备第一次社招
// 思路: 排序加头尾指针. 从左到右遍历确定第一个数i, 然后在i后面的的头尾确定第二第三个数. 
// 注意: 为了不出现重复数, 先排序, 然后每次移动三个数中任意一个数都需要确保后面不相等

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        if(nums.size()<3) 
            return result;

        sort(nums.begin(),nums.end());

        int i=0;
        while(i<nums.size())
        // for(int i=0; i<nums.size(); i++)
        {
            if(nums[i]>0) 
                break;        //提前终止循环

            int left = i+1;
            int right = nums.size()-1;
            while(left<right) 
            {
                if(nums[left]+nums[right]+nums[i]<0)            
                    left++;            
                else if(nums[left]+nums[right]+nums[i]>0)
                    right--;
                else
                {
                    result.push_back({nums[i],nums[left],nums[right]});
                    while(left<right&&left+1<nums.size()&&nums[left]==nums[left+1])
                        left++;
                    while(left<right&&right-1>=0&&nums[right]==nums[right-1])
                        right--;
                    left++;
                    right--;
                }
            }
            // 避免nums[i]作为第一个数重复出现
            while(i+1<nums.size()&&nums[i] == nums[i+1])
                i++;    
            i++;        
        }
        return result;
    }
};


int main()
{
    Solution s;
    vector<int> v = {0,0,0,0};
    s.threeSum(v);
    return 0;
}