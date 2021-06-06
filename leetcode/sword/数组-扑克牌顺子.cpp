// 剑指 Offer 61. 扑克牌中的顺子
// 从扑克牌中随机抽5张牌，判断是不是一个顺子，即这5张牌是不是连续的。2～10为数字本身，A为1，J为11，Q为12，K为13，而大、小王为 0 ，可以看成任意数字。A 不能视为 14。

// 示例 1:
// 输入: [1,2,3,4,5]
// 输出: True
 
// 示例 2:
// 输入: [0,0,1,2,5]
// 输出: True

// -------------------第三次刷-----------------------
// 2021年6月3日15:56:28
// 准备第一次社招
// 思路: 先获得0的数量, 然后排序, 不连续的中间差个数小于0的数量即可为顺子
// 注意: 不能有两张牌相等
// 注意: 不能用0去算sub

#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        int zero_num = 0;
        for(int i=0;i<nums.size();i++){
            if(nums[i] == 0)
                zero_num++;
        }
        sort(nums.begin(), nums.end());

        int sub=0;
        int index=0;
        while(nums[index]==0&&index<nums.size())
            index++;
        
        while(index<nums.size()){
            if(index-1>=0){
                if(nums[index]-nums[index-1]==0)//不能有两张牌相等
                    return false;
                if(nums[index-1]!=0)//不能用0去算sub
                    sub+=nums[index]-(nums[index-1]+1);
            }
            index++;
        }

        return sub<=zero_num;
    }
};


//page 298
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    // bool IsContinuous( vector<int> numbers ) {
    //     if(numbers.size()!=5)
    //         return false;

    //     sort(numbers.begin(),numbers.end());
    //     int num_0=0;
    //     int num_break=0;
    //     for(int i=0;i<numbers.size()-1;i++)
    //     {
    //         if(numbers[i]==0)
    //             continue;
    //         if(numbers[i]==numbers[i+1])
    //             return false;
    //     }
    //     for(int i=0;i<numbers.size();i++)
    //     {
    //         if(numbers[i]==0)
    //             num_0++;
    //     }
    //     for(int i=0;i<numbers.size()-1;i++)
    //     {
    //         if(numbers[i]==0)
    //             continue;
    //         if(numbers[i+1]-numbers[i]>1)
    //             num_break+=numbers[i+1]-numbers[i]-1;
    //     }

    //     if(num_break>num_0)
    //         return false;
    //     else
    //         return true;

    // }
    bool IsContinuous(vector<int> numbers)
    {
        if(numbers.size()<5)
            return false;
        
        sort(numbers.begin(),numbers.end());

        int king_num = 0;
        int split_num=0;
        for(int i=0;i<numbers.size()-1;i++)
        {
            if(numbers[i]==0)
                king_num++;
            else if(numbers[i+1]-numbers[i]==0)
                return false;
            else if(numbers[i+1]-numbers[i]==1)
                continue;
            else
                split_num+=numbers[i+1]-numbers[i]-1;
        }
        if(numbers[numbers.size()-1]==0)
                king_num++;

        return king_num>=split_num;

    }
};

int main()
{
    vector<int> numbers{1, 3, 2, 5, 4};

    Solution solution;
    bool result = solution.IsContinuous(numbers);
    return 0;
}