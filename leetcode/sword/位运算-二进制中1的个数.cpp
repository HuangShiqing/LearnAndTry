// 剑指 Offer 15. 二进制中1的个数
// 请实现一个函数，输入一个整数（以二进制串形式），输出该数二进制表示中 1 的个数。例如，把 9 表示成二进制是 1001，有 2 位是 1。因此，如果输入 9，则该函数输出 2。

// 示例 1：
// 输入：00000000000000000000000000001011
// 输出：3
// 解释：输入的二进制串 00000000000000000000000000001011 中，共有三位为 '1'。

// 示例 2：
// 输入：00000000000000000000000010000000
// 输出：1
// 解释：输入的二进制串 00000000000000000000000010000000 中，共有一位为 '1'。

// 示例 3：
// 输入：11111111111111111111111111111101
// 输出：31
// 解释：输入的二进制串 11111111111111111111111111111101 中，共有 31 位为 '1'。
 
// 提示：
// 输入必须是长度为 32 的 二进制串 。

// -------------------第三次刷-----------------------
// 2021年5月11日14:52:37
// 准备第一次社招
// 思路: 很简单, 数n与1按位&, 不多说
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int r=0;
        do {
            r+=(n&1);
            n = n>>1;
        }
        while(n>0);
        return r;
    }
};


#include <iostream>

class Solution
{
public:
    // int NumberOf1(int n)
    // {        
    //     unsigned int bit=1;
    //     int number=0;

    //     while(bit)
    //     {
    //         if(n&bit)
    //             number++;
    //         //不要右移动数n本身，左移动bit
    //         bit=bit<<1;
    //     }
    //     return number;

    // }
    int NumberOf1(int n)
    {
        int number=0;

        while(n)
        {
            //一个数减去1后再跟原数&可以将原数最右边的1变成0
            n = (n-1)&n;
            number++;
        }
        return number;
    }
};

int main()
{
    // int n = 9;
    // int  count =0;
    // while(n)
    // {
    //     if(n&1)
    //         count ++;
    //     n = n >> 1;
    // }
    // int n = 9;
    // int count = 0;
    // int temp = 1;
    // while(temp)
    // {
    //     if (n&temp)
    //         count ++;
    //     temp = temp << 1;
    // }
    int n = -9;
    Solution solution;
    int r = solution.NumberOf1(n);
    return 0;
}