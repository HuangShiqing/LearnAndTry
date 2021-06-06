// 剑指 Offer 51. 数组中的逆序对
// 在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

// 示例 1:
// 输入: [7,5,6,4]
// 输出: 5

// -------------------第三次刷-----------------------
// 2021年5月31日14:48:44
// 准备第一次社招
// 思路: 归并, 过程不算难, 主要是要根据题意想到归并

#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int count=0;
    void MergeSort(vector<int>& nums, int start, int end){
        if(start == end)
            return;
        // 这里相差1的情况是可以走下面的, 可以不特殊处理
        // if(start +1 ==end){
        //     if(nums[start]>nums[end]){
        //         count++;
        //         swap(nums[start], nums[end]);
        //     }            
        //     return;                
        // }

        int middle = (start+end)/2;
        MergeSort(nums, start, middle);
        MergeSort(nums, middle+1, end);

        int p1=start;
        int p2 = middle+1;
        vector<int> v;
        while(p1<=middle&&p2<=end){
            if(nums[p1]>nums[p2]){
                v.push_back(nums[p2++]);
                count+=(middle-p1+1);//当p1>p2时, 由于p1已经是升序了, 那么p1后面的数肯定都大于p2           
            }
            else
                v.push_back(nums[p1++]);
        }
        while(p1<=middle){
            v.push_back(nums[p1++]);
        }
        while(p2<=end){
            if(nums[p1]>nums[p2])
                count++;
            v.push_back(nums[p2++]);
        }

        for (int i = 0; i < v.size(); i++)
            nums[start + i] = v[i];
    }

    int reversePairs(vector<int>& nums) {
        if(nums.size()==0)
            return count;
        MergeSort(nums, 0, nums.size()-1);
        return count;
    }
};




//page 249
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int number;
    void MergeSort(vector<int> &data, int start, int end)
    {
        if (end - start == 0)
            return;
        if (end - start == 1)
        {
            if (data[start] > data[end])
            {
                swap(data[start], data[end]);
                number++;
            }
            return;
        }

        int middle = (start + end) / 2;
        MergeSort(data, start, middle);
        MergeSort(data, middle + 1, end);

        //跟归并排序不一样的地方就是这里需要从大到小进行合并
        int p1 = middle;
        int p2 = end;
        vector<int> v;
        while (p1 >= start && p2 >= middle + 1)
        {
            if (data[p1] > data[p2])
            {
                v.push_back(data[p1--]);

                //p2前面的都是能够构成逆序对的数
                number += p2 - middle;
                //每次更新也要求余
                if (number >= 1000000007) //数值过大求余                
                    number %= 1000000007;
            }
            else
                v.push_back(data[p2--]);
        }
        while (p1 >= start)
        {
            if (data[p1] > data[p2])
                number++;
            v.push_back(data[p1--]);
        }

        while (p2 >= middle + 1)
            v.push_back(data[p2--]);
        reverse(v.begin(), v.end());
        for (int i = 0; i < v.size(); i++)
            data[start + i] = v[i];
    }

    int InversePairs(vector<int> data)
    {
        if (data.size() == 0)
            return 0;
        MergeSort(data, 0, data.size() - 1);
        return number % 1000000007;
    }
};

int main()
{
    vector<int> v{364, 637, 341, 406, 747, 995, 234, 971, 571, 219, 993, 407, 416, 366, 315, 301, 601, 650, 418, 355, 460, 505, 360, 965, 516, 648, 727, 667, 465, 849, 455, 181, 486, 149, 588, 233, 144, 174, 557, 67, 746, 550, 474, 162, 268, 142, 463, 221, 882, 576, 604, 739, 288, 569, 256, 936, 275, 401, 497, 82, 935, 983, 583, 523, 697, 478, 147, 795, 380, 973, 958, 115, 773, 870, 259, 655, 446, 863, 735, 784, 3, 671, 433, 630, 425, 930, 64, 266, 235, 187, 284, 665, 874, 80, 45, 848, 38, 811, 267, 575};
    Solution solution;
    int r = solution.InversePairs(v);
    return 0;
}