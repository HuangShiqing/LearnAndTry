#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
// 双指针：left 指针指向数组的开始；right 指针指向数组的结尾。
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
                iter_swap(nums.begin() + index, nums.begin() + left);
                left++;
                index++;
            }
            else if(nums[index] == 1)
                index++;
            else if(nums[index]==2)
            {
                iter_swap(nums.begin() + index, nums.begin() + right);
                right--;
            }
        }
    }
};