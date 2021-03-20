#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;


class Solution {
public:
    // 遍历一遍建立值和索引的map，然后再遍历并从map中找是否有差值
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