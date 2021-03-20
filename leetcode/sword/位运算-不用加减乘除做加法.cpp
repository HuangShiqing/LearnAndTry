//page 310
#include <stdio.h>
#include <iostream>
using namespace std;
class Solution
{
public:
    // int Add(int num1, int num2)
    // {
    //     int sum,carry;
    //     do
    //     {
    //         sum = num1^num2;
    //         carry = (num1&num2)<<1;
    //         num1 = sum;
    //         num2 =carry;
    //     }
    //     while(num2!=0);
    //     return num1;
    // }
    int Add(int num1, int num2)
    {
        //把加法分成2步，第一步用异或^代替不进位的相加，第二步用相与&后左移一位代替进位相加
        int sum, carry;
        do
        {
            sum = num1 ^ num2;
            //因为最高位是符号位，所以不用
            carry = (num1 & num2) << 1;

            num1 = sum;
            num2 = carry;
        } while (carry);//进位相加后还可能再产生新的进位
        //负数的补码也是对的，但是分析起来很复杂
        //返回也是int代表不考虑溢出
        return sum;
    }
};

int main()
{
    int num1=-1;
    cout<<hex<<num1<<endl;
    printf("%x",num1);
    // int num1 = 0x80000001;
    int num2 = 0x00000000;
    Solution solution;
    int r = solution.Add(num1, num2);
    return 0;
}