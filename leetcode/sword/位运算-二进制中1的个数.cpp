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