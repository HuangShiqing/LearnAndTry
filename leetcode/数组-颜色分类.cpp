#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 75. 颜色分类
// 给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
// 此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

// 示例 1：
// 输入：nums = [2,0,2,1,1,0]
// 输出：[0,0,1,1,2,2]

// 示例 2：
// 输入：nums = [2,0,1]
// 输出：[0,1,2]

// 示例 3：
// 输入：nums = [0]
// 输出：[0]

// 示例 4：
// 输入：nums = [1]
// 输出：[1]

// -------------------第二次刷-----------------------
// 2021年6月11日10:46:00
// 准备第一次社招
// 思路:
// 三指针：left 指针指向数组的开始；right 指针指向数组的结尾。滑动index
// 若 index 位置上的元素值为 0，则说明是红色，要放在最前面，即和 left 指针指向位置上的元素进行交换；
// 若 index 位置上的元素值为 1，则说明是白色（本来就是要放在中间）不需要进行交换，直接将 index 指针后移；
// 若 index 位置上的元素值为 2，则说明是蓝色，要放在最后面，即和 right 指针指向位置上的元素进行交换。
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        int index = 0;
        while (index <= right) {
            if (nums[index] == 0) {
                // iter_swap(nums.begin() + index, nums.begin() + left);
                swap(nums[index], nums[left]);
                left++;
                index++;
            }
            else if(nums[index] == 1)
                index++;
            else if(nums[index]==2)
            {
                // iter_swap(nums.begin() + index, nums.begin() + right);
                swap(nums[index], nums[right]);
                right--;
            }
        }
    }
};