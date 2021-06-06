// 剑指 Offer 67. 把字符串转换成整数
// 写一个函数 StrToInt，实现把字符串转换成整数这个功能。不能使用 atoi 或者其他类似的库函数。

// 首先，该函数会根据需要丢弃无用的开头空格字符，直到寻找到第一个非空格的字符为止。
// 当我们寻找到的第一个非空字符为正或者负号时，则将该符号与之后面尽可能多的连续数字组合起来，作为该整数的正负号；假如第一个非空字符是数字，则直接将其与之后连续的数字字符组合起来，形成整数。
// 该字符串除了有效的整数部分之后也可能会存在多余的字符，这些字符可以被忽略，它们对于函数不应该造成影响。

// 注意：假如该字符串中的第一个非空格字符不是一个有效整数字符、字符串为空或字符串仅包含空白字符时，则你的函数不需要进行转换。
// 在任何情况下，若函数不能进行有效的转换时，请返回 0。

// 说明：
// 假设我们的环境只能存储 32 位大小的有符号整数，那么其数值范围为 [−231,  231 − 1]。如果数值超过这个范围，请返回  INT_MAX (231 − 1) 或 INT_MIN (−231) 。

// 示例 1:
// 输入: "42"
// 输出: 42

// 示例 2:
// 输入: "   -42"
// 输出: -42
// 解释: 第一个非空白字符为 '-', 它是一个负号。
//      我们尽可能将负号与后面所有连续出现的数字组合起来，最后得到 -42 。

// 示例 3:
// 输入: "4193 with words"
// 输出: 4193
// 解释: 转换截止于数字 '3' ，因为它的下一个字符不为数字。

// 示例 4:
// 输入: "words and 987"
// 输出: 0
// 解释: 第一个非空字符是 'w', 但它不是数字或正、负号。
//      因此无法执行有效的转换。

// 示例 5:
// 输入: "-91283472332"
// 输出: -2147483648
// 解释: 数字 "-91283472332" 超过 32 位有符号整数范围。 
//      因此返回 INT_MIN (−231) 。

// -------------------第三次刷-----------------------
// 2021年06月05日08:54:37
// 准备第一次社招
// 思路: 这题的难点是如何考虑所有的情况
// 1. 首尾空格
// 2. 首字符为+-号
// 3. int表示范围, 赋值前先判断范围, 超出直接返回.if(num*10+(str[index]-'0')>INT_MAX)
// 4. 超出范围后INT_MIN和INT_MAX不一样

class Solution {
public:
    int strToInt(string str) {
        if(str.size()==0)
            return 0;

        int index=0;
        while(str[index]==' ')
            index++;
        
        bool flag=1;
        if('0'<=str[index]&&str[index]<='9')
            ;
        else{
            if(str[index]=='+')
                index++;
            else if(str[index]=='-'){
                flag=0;
                index++;
            }
            else
                return 0;
        }
            
        long num=0;
        while(index<str.size()){
            if('0'<=str[index]&&str[index]<='9'){
                
                if(num*10+(str[index]-'0')>INT_MAX){
                    if(flag==0)
                        return INT_MIN;
                    else
                        return INT_MAX; 
                }
                    
                num=num*10+(str[index]-'0');
                index++;
            }
            // else if(' '==str[index])
            //     index++;
            else
                break;
        }


        if(flag==0)
            num = -num;
        
        if(num>INT_MAX)
            return INT_MAX;
        else if(num<INT_MIN)
            return INT_MIN;
        else
            return num;
    }
};

//page 318
#include <string>
using namespace std;

class Solution
{
public:
    // bool g_flag = true;

    // int StrToInt(string str)
    // {
    //     int flag = 1;
    //     long long carry = 1;
    //     long long sum = 0;

    //     if (str == "")
    //         return 0;

    //     string::iterator iter = str.end() - 1;

    //     // for (int i = 0; i < str.size(); i++)

    //     if (str[0] == '+')
    //         flag = 1;
    //     else if (str[0] == '-')
    //         flag = -1;

    //     while (iter != str.begin() - 1)
    //     {
    //         if (iter == str.begin() && ((*iter == '+') || (*iter == '-')))
    //         {
    //             iter--;
    //             break;
    //         }

    //         if (*iter >= '0' && *iter <= '9')
    //         {
    //             sum += carry * flag * (*iter - '0');
    //             carry *= 10;
    //             if(sum>INT32_MAX||sum<INT32_MIN)
    //                 return 0;
    //         }
    //         else
    //         {
    //             return 0;
    //         }
    //         iter--;
    //     }
    //     return sum;
    // }

    int StrToInt(string str)
    {
        if (str.size() == 0)
            return 0;
        int bit = 1;
        int num = 0;

        

        for (int i = str.size() - 1; i > 0; i--)
        {
            if (str[i] >= '0' && str[i] <= '9')
            {
                num += (bit * (str[i] - '0'));
                bit *= 10;
            }
            else
                return 0;
        }

        int a = 1;
        if (str[0] == '-')
            a = -1;
        else if (str[0] == '+')
            a = 1;
        else
        {
            if (str[0] >= '0' && str[0] <= '9')
            {
                num += (bit * (str[0] - '0'));
                bit *= 10;
            }
            else
                return 0;
        }
        
        return a*num;
    }
};

int main()
{
    string s = "-3251";
    Solution solution;
    int sum = solution.StrToInt(s);
    return 0;
}