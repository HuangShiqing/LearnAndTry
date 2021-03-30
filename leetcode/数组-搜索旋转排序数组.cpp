#include <vector>
using namespace std;

class Solution {
public:
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
