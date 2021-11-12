#include <vector>
using namespace std;

// 33. 搜索旋转排序数组
// 整数数组 nums 按升序排列，数组中的值 互不相同 。
// 在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。
// 给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。

// 示例 1：
// 输入：nums = [4,5,6,7,0,1,2], target = 0
// 输出：4

// 示例 2：
// 输入：nums = [4,5,6,7,0,1,2], target = 3
// 输出：-1

// 示例 3：
// 输入：nums = [1], target = 0
// 输出：-1

// -------------------第二次刷-----------------------
// 2021年6月8日15:55:01
// 准备第一次社招
// 思路1: 即使不是全部有序, 也可以直接二分. 先根据left, right, middle判断当前处于哪一段有序数组. 
// 然后就一般的二分判断. target位于middle左侧, 则缩小右界, 否则缩小左界
class Solution {
public:
    int search(const vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size()-1;
        int middle = (left+right)/2;
        while(left<=right){
            if(nums[middle] == target)
                return middle;
            
            if(nums[left]<=nums[middle]){//左半段
                if(nums[left]<=target&&target<=nums[middle])
                    right = middle - 1;
                else
                    left = middle + 1;
            }
            else{//右半段
                if(nums[middle]<target&&target<=nums[right])
                    left = middle + 1;
                else
                    right = middle - 1;
            }
            middle = (left+right)/2;
        }
        return -1;
    }

    // 思路2: 相比之下这个有点不优雅了. 复杂度是n+logn=n了
    int search(const vector<int>& nums, int target) {
        // 处理异常
        if (nums.size() == 0)
            return -1;
        else if (nums.size() == 1) {
            if (nums[0] == target)
                return 0;
            else
                return -1;
        }

        // 第一步,找到变化点
        int change = -1;
        int left;
        int right;
        int middle;
        for (int i = 0; i < nums.size() - 1; i++)
            if (nums[i] > nums[i + 1])
                change = i;
        if (change == -1) {  //唯一的特殊情况就是当变化点i==0时此时数组还是维持升序
            left = 0;
            right = nums.size() - 1;
        } else {  //简单判断找到二分范围是左边还是右边
            if (target >= nums[0]) {
                left = 0;
                right = change;
            } else if (target <= nums[nums.size() - 1]) {
                left = change + 1;
                right = nums.size() - 1;
            }
        }
        middle = (left + right) / 2;

        //二分
        while (left <= right) {
            if (nums[middle] == target)
                return middle;
            else if (nums[middle] < target)
                left = middle + 1;
            else
                right = middle - 1;

            middle = (left + right) / 2;
        }
        return -1;
    }
};

int main(int argc, char const* argv[]) {
    Solution s;
    s.search({3, 1}, 1);
    return 0;
}
