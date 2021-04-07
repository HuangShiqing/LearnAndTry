#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

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
