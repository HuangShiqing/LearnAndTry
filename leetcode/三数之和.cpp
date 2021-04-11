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
                    while(left<right&&nums[left]==nums[left+1]&&left<nums.size()-1-1)
                        left++;
                    while(left<right&&nums[right]==nums[right-1])
                        right--;
                    left++;
                    right--;
                }
            }
            // 避免nums[i]作为第一个数重复出现
            while(nums[i] == nums[i+1]&&i+1<nums.size())
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