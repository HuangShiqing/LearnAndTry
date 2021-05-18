// 剑指 Offer 16. 数值的整数次方
// 实现 pow(x, n) ，即计算 x 的 n 次幂函数（即，xn）。不得使用库函数，同时不需要考虑大数问题。

// 示例 1：
// 输入：x = 2.00000, n = 10
// 输出：1024.00000

// 示例 2：
// 输入：x = 2.10000, n = 3
// 输出：9.26100

// 示例 3：
// 输入：x = 2.00000, n = -2
// 输出：0.25000
// 解释：2-2 = 1/22 = 1/4 = 0.25

// 提示：
// -100.0 < x < 100.0
// -231 <= n <= 231-1
// -104 <= xn <= 104

// -------------------第三次刷-----------------------
// 2021年5月11日14:52:37
// 准备第一次社招
// 思路: 就for循序乘呗, 需要考虑n为负数的情况. 结果超时了

class Solution {
public:
    double myPow(double x, int n) {
        double r=1;
        if(n==0){
            return 1;
        }
        else if(n>0){
            for(int i=0;i<n;i++){
                r*=x;
            }
        }
        else if(n<0){
            for(int i=0;i<-n;i++){//把n反成正数然后和上面一样操作
                r*=x;
            }
            if(r==0)//要防止除以0的情况
                r = 0;
            else
                r = 1/r;//取倒数
        }
        return r;
    }
};


//page 111
#include <iostream>
#include <math.h>
class Solution
{
public:
    // double Power(double base, int exponent)
    // {
    //     if (base == 0)
    //         return 0;
    //     else if (exponent == 0)
    //         return 1;

    //     int abs_exponent = abs(exponent);
    //     double result = 1;
    //     while (abs_exponent)
    //     {
    //         result *= base;
    //         abs_exponent--;
    //     }

    //     if (exponent < 0)
    //         return 1 / result;
    //     else
    //         return result;
    // }

    // double Power2_uint(double base, unsigned int exponent)
    // {
    //     if (base == 0)
    //         return 0;
    //     else if (exponent == 0)
    //         return 1;

    //     double result = 0;
    //     if (exponent == 1)
    //     {
    //         return base;
    //     }
    //     else if (exponent % 2 == 0) //偶数
    //     {
    //         result = Power2_uint(base, exponent / 2);
    //         result *= result;
    //     }
    //     else
    //     {
    //         result = Power2_uint(base, (exponent - 1) / 2);
    //         result *= result;
    //         result *= base;
    //     }
    //     return result;
    // }
    // double Power2(double base, int exponent)
    // {
    //     int abs_exponent = abs(exponent);
    //     double result = 1;
    //     result = Power2_uint(base,abs_exponent);

    //     if (exponent < 0)
    //         return 1 / result;
    //     else
    //         return result;
    // }
    double Power(double base, int exponent)
    {
        double r = 1;
        if (exponent < 0)
        {
            for (int i = 0; i < -exponent; i++)
                r *= base;

            if (r == 0)
                return 0;
            else
                return 1.0 / r;
        }
        else
        {
            for (int i = 0; i < exponent; i++)
                r *= base;
            return r;
        }
    }

    double Power2_uint(double base, unsigned int exponent)
    {
        //注意这里当是0和1的时候停止递归
        if (exponent == 0)
            return 1;
        if (exponent == 1)
            return base;

        double r = Power2_uint(base, exponent / 2);
        if (exponent % 2 == 0)
            return r * r;
        else
            return r * r * base;
    }
};

int main()
{
    double base = 2;
    int exponent = -2;

    Solution solution;
    double a = solution.Power(base, exponent);

    return 0;
}