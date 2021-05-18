// page 82
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    // 超算那个思路不对，二分还是用来找lef和right相邻时退出
    int minNumberInRotateArray(vector<int> rotateArray) {
        if (rotateArray.size() == 0)
            return 0;

        int left = 0;
        int right = rotateArray.size() - 1;
        int mid = (left + right) / 2;
        while (left <= right) {
            // 当mid数大于left数，则转折点在mid的右边
            if (rotateArray[mid] >= rotateArray[left])
                left = mid;
            else
                right = mid;
            mid = (left + right) / 2;

            // 当left和right相邻则找到退出
            if (abs(left - right) == 1)
                return rotateArray[right];
        }
    }
    int minNumberInRotateArray(vector<int> rotateArray) {
        if (rotateArray.size() == 0)
            return 0;

        int left = 0;
        int right = rotateArray.size() - 1;
        int mid = (left + right) / 2;
        // while(rotateArray[left]>=rotateArray[right])
        while (1) {
            if (abs(left - right) == 1) {
                return rotateArray[right];
            }

            //三者相等只能顺序查找
            if (rotateArray[left] == rotateArray[right] && rotateArray[mid] == rotateArray[left]) {
                int temp = left;
                for (int i = left + 1; i <= right; i++) {
                    if (rotateArray[i] < rotateArray[temp])
                        temp = i;
                }
                return rotateArray[temp];
            }

            if (rotateArray[mid] >= rotateArray[left])
                left = mid;
            else
                right = mid;
            mid = (left + right) / 2;
        }
    }
};

// 剑指 Offer 11. 旋转数组的最小数字
// 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如，数组
// [3,4,5,1,2] 为 [1,2,3,4,5] 的一个旋转，该数组的最小值为1。
// 示例 1： 输入：[3,4,5,1,2] 输出：1
// 示例 2： 输入：[2,2,2,0,1] 输出：0

// 2021年04月25日22:41:25
// 准备第一次社招
// 思路:
// 二分肯定是二分, 这里就是退出条件变了, 退出条件变成当left与right相邻. 有个特殊情况就是三者一样
// 之前的代码在leetcode上是错的, shift
class Solution {
public:
    int minArray(vector<int>& numbers) {
        if (!numbers.size())
            return -1;
        int left = 0;
        int right = numbers.size() - 1;
        int middle = (left + right) / 2;
        // while(left<=right){
        while(1){
            if(abs(left-right)==1)
                return numbers[right];

            //三者相等只能顺序查找
            if (numbers[left] == numbers[right] && numbers[middle] == numbers[left]) {
                int temp = left;
                for (int i = left + 1; i <= right; i++) {
                    if (numbers[i] < numbers[temp])
                        temp = i;
                }
                return numbers[temp];
            }

            if(numbers[middle] >= numbers[left])
                left = middle;
            else
                right = middle;
            middle = (left + right) / 2;
        }
        return -1;
    }
};