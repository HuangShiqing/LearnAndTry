// 88. 合并两个有序数组
// 给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。
// 初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。你可以假设 nums1 的空间大小等于 m + n，这样它就有足够的空间保存来自 nums2 的元素。

// 示例 1：
// 输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
// 输出：[1,2,2,3,5,6]

// 示例 2：
// 输入：nums1 = [1], m = 1, nums2 = [], n = 0
// 输出：[1]

#include <vector>
using namespace std;

// -------------------第二次刷-----------------------
// 2021年7月19日15:52:25
// 准备第一次社招
// 思路: 双尾指针

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = m-1;
        int p2 = n-1;
        int p3 = m+n-1;
        int current;
        while(p1>=0||p2>=0){
            if(p1==-1){
                current = nums2[p2];
                p2--;
            }
            else if(p2==-1){
                current = nums1[p1];
                p1--;
            }
            else if(nums1[p1]>nums2[p2]){
                current = nums1[p1];
                p1--;
            }
            else{
                current = nums2[p2];
                p2--;
            }
            nums1[p3] = current;
            p3--;
        }
    }
};