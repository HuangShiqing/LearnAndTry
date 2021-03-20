#include <iostream>
#include <math.h>
using namespace std;

class Solution
{
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
    int cutRope(int number)
    {
        if(number<=1)
            return 0;
        if(number==2)
            return 1;
        if(number==3)
            return 2;
        if(number==4)
            return 4;
        //当n>=5时，可以证明3(n-3)>=2(n-2)
        int num_3 = number/3;
        //当余下的是1时，退掉一个3,2*2要大于3*1
        if(number-num_3*3==1)
            num_3--;
        int num_2 = (number-num_3*3)/2;
        return (int)(pow(3,num_3))*(int)(pow(2,num_2));
    }
};


int main()
{
    int number=4;
    Solution solition;
    int max = solition.cutRope(number);

    return 0;
}
