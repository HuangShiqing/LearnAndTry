#include <math.h>

#include <iostream>
using namespace std;

// 剑指 Offer 14- I. 剪绳子
// 给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为
// k[0],k[1]...k[m-1] 。请问 k[0]*k[1]*...*k[m-1]
// 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。

// 示例 1：
// 输入: 2
// 输出: 1
// 解释: 2 = 1 + 1, 1 × 1 = 1
// 示例 2:
// 输入: 10
// 输出: 36
// 解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36

// 2021年5月11日14:52:37
// 准备第一次社招
// 思路1: 死记切分规则
// 最佳为3, 尽可能把绳子切为多个长度为3的片段
// 剩下的绳子为2时保留
// 剩下的绳子为1时, 取一个3与之组成两个长度为2的片段, 因为2*2>3*1

class Solution {
public:
    int cuttingRope(int n){

        if(n==2)
            return 1;
        else if(n==3)
            return 2;
        else if(n==4)
            return 2*2;

        int r = 1;
        while (n>=3) {
            r*=3;
            n-=3;
        }

        if(n==2)
            r*=2;
        else if(n==1){
            r/=3;
            r = r*2*2;
        }
        return r; 
    }
};

class Solution {
public:
    // int cutRope(int number)
    // {
    //     if (number < 2)
    //         return 0;
    //     if (number == 2)
    //         return 1;
    //     if (number == 3)
    //         return 2;

    //     int *products = new int[number + 1];
    //     products[0] = 0;
    //     products[1] = 1;
    //     products[2] = 2;
    //     products[3] = 3;

    //     int max = 0;
    //     for (int i = 4; i <= number; i++)
    //     {
    //         max = 0;
    //         for (int j = 1; j <= i / 2; j++)
    //         {
    //             if (products[j] * products[i - j] > max)
    //             {
    //                 max = products[j] * products[i - j];
    //                 products[i] = max;
    //             }
    //         }
    //     }
    //     max = products[number];
    //     delete[] products;
    //     return max;
    // }
    int cutRope(int number) {
        if (number <= 1)
            return 0;
        if (number == 2)
            return 1;
        if (number == 3)
            return 2;
        if (number == 4)
            return 4;
        //当n>=5时，可以证明3(n-3)>=2(n-2)
        int num_3 = number / 3;
        //当余下的是1时，退掉一个3,2*2要大于3*1
        if (number - num_3 * 3 == 1)
            num_3--;
        int num_2 = (number - num_3 * 3) / 2;
        return (int)(pow(3, num_3)) * (int)(pow(2, num_2));
    }
};

int main() {
    int number = 4;
    Solution solition;
    int max = solition.cutRope(number);

    return 0;
}
