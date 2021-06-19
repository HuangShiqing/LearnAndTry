#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

// 215. 数组中的第K个最大元素
// 在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

// 示例 1:
// 输入: [3,2,1,5,6,4] 和 k = 2
// 输出: 5

// 示例 2:
// 输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
// 输出: 4

// -------------------第二次刷-----------------------
// 2021年06月13日11:15:42
// 准备第一次社招
// 思路: 用大小堆把数组分成两个部分. 参考求数据流的中位数

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> min_heap;
        priority_queue<int, vector<int>, less<int>> max_heap;

        for(int i=0;i<nums.size();i++){
            if(min_heap.size()<k){
                min_heap.push(nums[i]);
            }
            else{
                if(nums[i]>min_heap.top()){
                    int tmp = min_heap.top();
                    min_heap.pop();
                    min_heap.push(nums[i]);
                    max_heap.push(tmp);
                }else{
                    max_heap.push(nums[i]);
                }
            }
        }
        return min_heap.top();
    }
};