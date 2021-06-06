// 剑指 Offer 45. 把数组排成最小的数
// 输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。

// 示例 1:
// 输入: [10,2]
// 输出: "102"

// 示例 2:
// 输入: [3,30,34,5,9]
// 输出: "3033459"

// -------------------第三次刷-----------------------
// 2021年5月28日14:36:41
// 准备第一次社招
// 思路: 可以用系统自带的sort来一一比较所有元素, 比较的函数就按照题目的意思来, a和b分别前后拼成A和用后前拼成B, 比较AB即可(string可直接比较)
//

class Solution {
public:
    //需要静态函数
    static bool cmp(int a, int b){
        string A = to_string(a)+to_string(b);
        string B = to_string(b)+to_string(a);
        return A<B;
    }

    string minNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), cmp);
        string res;
        for(int i=0;i<nums.size();i++){
            res+=to_string(nums[i]);
        }
        return res;
    }
};


#include <iostream>
#include <vector>
using namespace std;

static bool cmp(int a, int b)
{
    // 比如 "3" < "31"但是 "331" > "313"，所以要将二者拼接起来进行比较
    string A = to_string(a)+to_string(b);
    string B = to_string(b)+to_string(a);
    return A<B;
}
string PrintMinNumber(vector<int> numbers) {
    
    sort(numbers.begin(),numbers.end(),cmp);
    string res;
    for(int i = 0; i < numbers.size(); i++){
        res += to_string(numbers[i]);
    }
    return res;
}