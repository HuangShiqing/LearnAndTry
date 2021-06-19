// 128. 最长连续序列
// 给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
// 进阶：你可以设计并实现时间复杂度为 O(n) 的解决方案吗？

// 示例 1：
// 输入：nums = [100,4,200,1,3,2]
// 输出：4
// 解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。

// 示例 2：
// 输入：nums = [0,3,7,2,5,8,4,6,0,1]
// 输出：9

// -------------------第二次刷-----------------------
// 2021年6月18日11:12:32
// 准备第一次社招
// 思路: map的key是num, value是num所能组成的序列的长度. 如果num-1和num+1也存在, 那么新的length=left+right+1
// 注意: 记得更新左序列的最左边的数的value和右序列最右边的数的value. 其中的数的value已经不重要了, 因为不会再用到

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, int> map;
        int max_length = 0;
        for(int i = 0;i<nums.size();i++){
            if(map.count(nums[i])==0){//防止重复
                int left = 0, right = 0, length = 0;
                if(map.count(nums[i]-1)!=0)
                    left = map[nums[i]-1];            
                if(map.count(nums[i]+1)!=0)
                    right = map[nums[i]+1];
                
                length = left+right+1;
                map[nums[i]] = length;
                if(length > max_length)
                    max_length = length;
                
                if(map.count(nums[i]-1)!=0)
                    map[nums[i]-left] = length;//是最左边
                
                if(map.count(nums[i]+1)!=0)
                    map[nums[i]+right] = length;//是最右边
            }
            
        }
        return max_length;
    }
};
