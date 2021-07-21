#include <iostream>
#include <vector>
using namespace std;

// 287. 寻找重复数
// 给定一个包含 n + 1 个整数的数组 nums ，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。
// 假设 nums 只有 一个重复的整数 ，找出 这个重复的数 。
// 你设计的解决方案必须不修改数组 nums 且只用常量级 O(1) 的额外空间。

// 示例 1：
// 输入：nums = [1,3,4,2,2]
// 输出：2

// 示例 2：
// 输入：nums = [3,1,3,4,2]
// 输出：3

// 示例 3：
// 输入：nums = [1,1]
// 输出：1

// 示例 4：
// 输入：nums = [1,1,2]
// 输出：1
// 提示：
// 1 <= n <= 105
// nums.length == n + 1
// 1 <= nums[i] <= n
// nums 中 只有一个整数 出现 两次或多次 ，其余整数均只出现 一次
 
// 进阶：
// 如何证明 nums 中至少存在一个重复的数字?
// 你可以设计一个线性级时间复杂度 O(n) 的解决方案吗？

// -------------------第二次刷-----------------------
// 2021年7月2日10:59:10
// 准备第一次社招
// 思路1: 数字范围都在1到n之间, 那么就考虑把一个数nums[i]准备移动到nums[nums[i]]处, 移动前先发现两者相等则代表之前已经有
// 一个数移动到该处了, 代表这两数是相等的. 但是这题说不能修改nums. 那就按照之前说的先映射为链表. 入口是被两个对象指向的node. 
// node以及node->val都是i, node->next以及node->next->val是nums[i], node->next->next以及node->next->next->val是nums[nums[i]] 
// 然后用环形链表的方法来. 快慢指针找到相遇点, 然后再快慢指针p1 = head, p2 = slow找到相遇点就是入口
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0;
        int fast = 0;
        slow = nums[slow];
        fast = nums[nums[fast]];
        while(slow!=fast){
            slow = nums[slow];
            fast = nums[nums[fast]];
        }

        int pre1 = 0;
        int pre2 = slow;
        while(pre1 != pre2){
            pre1 = nums[pre1];
            pre2 = nums[pre2];
        }
        return pre1;
    }
};