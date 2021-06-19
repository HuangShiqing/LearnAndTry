#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 55. 跳跃游戏
// 给定一个非负整数数组 nums ，你最初位于数组的 第一个下标 。
// 数组中的每个元素代表你在该位置可以跳跃的最大长度。
// 判断你是否能够到达最后一个下标。

// 示例 1：
// 输入：nums = [2,3,1,1,4]
// 输出：true
// 解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。

// 示例 2：
// 输入：nums = [3,2,1,0,4]
// 输出：false
// 解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。

// -------------------第二次刷-----------------------
// 2021年6月10日11:42:59
// 准备第一次社招
// 思路1: 
// dfs卡时间
// class Solution {
// public:
//     bool canJump_repeat(vector<int>& nums, int index, unordered_map<int, bool>& map) {
//         if (index == nums.size() - 1)
//             return true;

//         for (int i = 1; i <= nums[index]; i++) {
//             if (map.find(index + i) != map.end()) {
//                 if (map[index + i] == true)
//                     return true;
//             } else {
//                 bool r = canJump_repeat(nums, index + i, map);
//                 map[index + i] = r;
//                 if (r)
//                     return true;
//             }
//         }
//         return false;
//     }
//     bool canJump(vector<int>& nums) {
//         unordered_map<int, bool> map;

//         if (canJump_repeat(nums, 0, map))
//             return true;
//         else
//             return false;
//     }
// };

// 思路2: 
// 1.如果某一个作为 起跳点 的格子可以跳跃的距离是 3，那么表示后面 3 个格子都可以作为 起跳点。
// 2.可以对每一个能作为 起跳点 的格子都尝试跳一次，把 能跳到最远的距离 不断更新。
// 3.如果可以一直跳到最后，就成功了。
bool canJump(vector<int>& nums) {
    int d = 0;//能跳到的最远index
    for (int i = 0; i < nums.size(); i++) {
        if (i > d)
            return false;
        d = max(d,i+nums[i]);//后面能跳的最远距离可能小于前面的
    }
    return true;
}
