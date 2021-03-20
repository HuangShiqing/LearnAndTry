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