// 剑指 Offer 57 - II. 和为s的连续正数序列
// 输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。
// 序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。

// 示例 1：
// 输入：target = 9
// 输出：[[2,3,4],[4,5]]

// 示例 2：
// 输入：target = 15
// 输出：[[1,2,3,4,5],[4,5,6],[7,8]]

// -------------------第三次刷-----------------------
// 2021年6月2日15:17:03
// 准备第一次社招
// 思路: 这里不是头尾双指针了, 因为头尾指针往中间靠都是减小和的操作, 没有增加和的操作. 那么就用双头指针. 增加和的操作为right++, 减小和的操作是left++
// 注意: 相等的时候要left++, 因为循环时以left为基准的, left找到唯一的一个序列后要增加

class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        int left = 1;
        int right = 0;//我这里是左右都闭
        int sum = 0;
        vector<vector<int>> vv;
        while(left<=target/2){//(target/2)+(target/2+1)肯定就已经大于target了, 后面就不用数了
            if(sum==target){
                vector<int> v;
                for(int i=left;i<=right;i++){
                    v.push_back(i);
                }
                vv.push_back(v);
                sum-=left;
                left++;
            }
            else if(sum < target){
                right++;
                sum+=right;
            }
            else{
                sum-=left;
                left++;
            }
        }

        return vv;
    }
};

//page:282
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
public:
    // vector<vector<int>> FindContinuousSequence(int sum)
    // {
    //     int start = 1;
    //     int end = 2;

    //     int sum_temp = 0;
    //     vector<int> v;
    //     vector<vector<int>> v2;
    //     for (int i = 1; i <= end; i++)
    //     {
    //         sum_temp += i;
    //         v.push_back(i);
    //     }

    //     //TODO:不懂这里为什么停止条件是（sum+1）/2
    //     int middle = (sum + 1) / 2;
    //     while (start < middle)
    //     {
    //         if (sum_temp == sum)
    //         {
    //             v2.push_back(v);                
    //             end++;
    //             v.push_back(end);
    //             sum_temp += end;
    //         }
    //         else if (sum_temp < sum)
    //         {

    //             end++;
    //             v.push_back(end);
    //             sum_temp += end;
    //         }
    //         else
    //         {
    //             sum_temp -= start;
    //             v.erase(v.begin());
    //             start++;
    //         }
    //     }
    //     return v2;
    // }
    vector<vector<int>> FindContinuousSequence(int sum)
    {
        vector<vector<int>> vv;
        
        if(sum<3)
            return vv;
        if(sum==3)
        {
            vector<int> v{1,2};
            vv.push_back(v);
            return vv;
        }

        int p1=1;
        int p2=2;
        while(p1<=sum/2)
        {
            int temp_sum=0;
            int temp_p=p1;
            while(temp_p<=p2)
            {
                temp_sum+=temp_p;
                temp_p++;
            }
            if(temp_sum==sum)
            {
                vector<int> v;
                temp_p=p1;
                while(temp_p<=p2)
                {
                    v.push_back(temp_p);
                    temp_p++;
                }
                vv.push_back(v);
                p1++;
            }
            else if (temp_sum<sum)
                p2++;
            else
                p1++;
            
        }
        return vv;
            
    }
};

int main()
{
    Solution solution;
    solution.FindContinuousSequence(15);
    return 0;
}