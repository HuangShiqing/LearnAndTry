// page 39
#include <iostream>
using namespace std;

class Solution {
public:
    // Parameters:
    //        numbers:     an array of integers
    //        length:      the length of array numbers
    //        duplication: (Output) the duplicated number in the array number
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    // bool duplicate(int numbers[], int length, int *duplication)
    // {

    //     if (numbers == nullptr || length <= 0)
    //         return false;

    //     for (int i = 0; i < length; i++)
    //     {
    //         if (numbers[i] > length - 1 || numbers[i] < 0)
    //             return false;
    //     }

    //     for (int i = 0; i < length; i++)
    //     {
    //         while (numbers[i] != i)
    //         {
    //             if (numbers[i] == numbers[numbers[i]])
    //             {
    //                 *duplication = numbers[i];
    //                 return true;
    //             }
    //             swap(numbers[i],numbers[numbers[i]]);
    //         }
    //     }

    //     return false;
    // }
    // TODO:不理解
    bool duplicate(int numbers[], int length, int* duplication) {
        if (numbers == nullptr || length < 0)
            return false;

        for (int i = 0; i < length; i++) {
            if (numbers[i] < 0 || numbers[i] >= length)
                return false;
        }
        for (int i = 0; i < length; i++) {
            while (numbers[i] != i) {
                if (numbers[i] == numbers[numbers[i]]) {
                    *duplication = numbers[i];
                    return true;
                }
                swap(numbers[i], numbers[numbers[i]]);
            }
        }
        return false;
    }
};

// 找出数组中重复的数字。
// 在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1
// 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
// 示例 1：
// 输入：
// [2, 3, 1, 0, 2, 5, 3]
// 输出：2 或 3
// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 2021年04月24日15:22:50
// 准备第一次社招

// 数组元素的 索引 和 值 是 一对多 的关系
// nums[nums[i]]代表的是nums[i]此时应该去的位置上的数
// nums[i]应该等于i才对, 不然nums[i]的正确位置应该是nums[nums[i]]
#include <vector>
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            while (nums[i] != i) {  // 一直交换直到满足nums[i] == i
                if (nums[i] == nums[nums[i]])
                    return nums[i];
                swap(nums[i], nums[nums[i]]);
            }
        }
        return -1;
    }
};