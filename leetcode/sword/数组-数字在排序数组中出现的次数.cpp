// 剑指 Offer 53 - I. 在排序数组中查找数字 I
// 统计一个数字在排序数组中出现的次数。

// 示例 1:
// 输入: nums = [5,7,7,8,8,10], target = 8
// 输出: 2

// 示例 2:
// 输入: nums = [5,7,7,8,8,10], target = 6
// 输出: 0

// -------------------第三次刷-----------------------
// 2021年6月1日10:04:34
// 准备第一次社招
// 思路: 两次二分. 检出条件变一下即可.
// 注意: 二分的时候更新left和right的时候是等于middle+-1的. 
// 注意: 返回前判断一下是否检出

#include <vector>
using namespace std;
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left_index = -1, right_index=-1;

        int left = 0;
        int right = nums.size() - 1;
        int middle = (left+right)/2;
        while(left<=right){
            if(nums[middle]<target){
                left = middle+1;
            }else if(nums[middle]>target)                {
                right = middle-1;
            }
            else{
                if(middle==0){
                    left_index = middle;
                    break;
                }
                else{
                    if(nums[middle-1]!=target){
                        left_index = middle;
                        break;
                    }
                    else
                        right = middle-1;
                }
                // if(nums[middle-1]!=target||middle==0){
                //     left_index = middle;
                //     break;
                // }
                // else{
                //     right = middle;
                // }
            }
            middle = (left+right)/2;
        }

        left = 0;
        right = nums.size() - 1;
        middle = (left+right)/2;
        while(left<=right){
            if(nums[middle]<target){
                left = middle+1;
            }else if(nums[middle]>target)                {
                right = middle-1;
            }
            else{
                if(middle==nums.size()-1){
                    right_index = middle;
                    break;
                }
                else{
                    if(nums[middle+1]!=target){
                        right_index = middle;
                        break;
                    }
                    else
                        left = middle+1;
                }
                // if(nums[middle+1]!=target||middle==nums.size()-1){
                //     right_index = middle;
                //     break;
                // }
                // else{
                //     left = middle;
                // }
            }
            middle = (left+right)/2;
        }
        
        if(left_index!=-1&&right_index!=-1)
            return right_index-left_index+1;
        else
            return 0;
    }
};

int main()
{
    vector<int> vdata{2,2};
    int k = 2;
    Solution solution;
    int result = solution.search(vdata, k);
    return 0;
} 

// //page 263
// #include <vector>
// using namespace std;

// class Solution
// {
// public:
//     // int GetFirstK_repeat(int data[],int length,int start,int end,int k)
//     // {
//     //     if(start>end)
//     //         return -1;
//     //     int middle = (start+end)/2;
//     //     int middle_data=data[middle];
//     //     if(middle_data==k)
//     //     {
//     //         if((middle>0&&data[middle-1]!=k)||middle==0)
//     //             return middle;
//     //         else
//     //         {
//     //             end = middle-1;
//     //         }
//     //     }
//     //     else if(middle>k)
//     //     end=middle-1;
//     //     else
//     //     {
//     //         start=middle+1;
//     //     }
//     //     return GetFirstK_repeat(data,length,start,end,k);
//     // }

//     // int GetNumberOfK(vector<int> data ,int k) {

//     //     int data_arry[data.size()];
//     //     int num=0;
//     //     int target;
//     //     for(int i =0;i<data.size();i++)
//     //     {
//     //         data_arry[i]=data[i];
//     //     }
//     //     int first_index = GetFirstK_repeat(data_arry,data.size(),0,data.size()-1,k);
//     //     target = data[first_index];
//     //     while(first_index<data.size()&&data[first_index]==target)
//     //     {
//     //         num++;
//     //         first_index++;
//     //     }
//     //     return num;
//     // }
//     // int GetNumberOfK(vector<int> data, int k)
//     // {
//     //     if (data.size() == 0)
//     //         return 0;
//     //     int left = 0;
//     //     int right = data.size() - 1;
//     //     int middle = (left + right) / 2;
//     //     int r = -1;
//     //     while (left <= right)
//     //     {
//     //         if (data[middle] == k)
//     //         {
//     //             r = middle;
//     //             break;
//     //         }
//     //         else if (data[middle] < k)
//     //             left = middle + 1;
//     //         else
//     //             right = middle - 1;
//     //         middle = (left + right) / 2;
//     //     }
//     //     if(r==-1)
//     //         return 0;

//     //     left = r;
//     //     right =r;
//     //     int num=0;
//     //     while(data[left]==k)
//     //     {
//     //         num++;
//     //         left--;
//     //     }
//     //     while(data[right]==k)
//     //     {
//     //         num++;
//     //         right++;
//     //     }
//     //     return --num;
//     // }

//     int GetNumberOfK(vector<int> data, int k)
//     {
//         if (data.size() == 0)
//             return 0;
//         int left = 0;
//         int right = data.size() - 1;
//         int middle = (left + right) / 2;
//         int r = -1;
//         while (left <= right)
//         {
//             if (data[middle] == k)
//             {
//                 if(middle>0)
//                 {
//                     if (data[middle - 1] == k)
//                     {
//                         right = middle - 1;
//                     }
//                     else
//                     {
//                         r = middle;
//                         break;
//                     }
//                 }
//                 else
//                 {
//                     r = middle;
//                     break;
//                 }                            
//             }
//             else if (data[middle] < k)
//                 left = middle + 1;
//             else
//                 right = middle - 1;
//             middle = (left + right) / 2;
//         }
//         if (r == -1)
//             return 0;

//         right = r;
//         int num = 0;
//         while (data[right] == k)
//         {
//             num++;
//             right++;
//         }
//         return num;
//     }
// };

// int main()
// {
//     vector<int> vdata{1, 2, 3, 3, 3, 3, 4, 5};
//     int k = 3;
//     Solution solution;
//     int result = solution.GetNumberOfK(vdata, k);
//     return 0;
// } 