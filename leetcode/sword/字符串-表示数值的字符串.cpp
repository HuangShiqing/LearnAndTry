// 剑指 Offer 20. 表示数值的字符串
// 请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。

// 数值（按顺序）可以分成以下几个部分：
//     1.若干空格
//     2.一个 小数 或者 整数
//     3.（可选）一个 'e' 或 'E' ，后面跟着一个 整数
//     4.若干空格

// 小数（按顺序）可以分成以下几个部分：
//     1.（可选）一个符号字符（'+' 或 '-'）
//     2.下述格式之一：
//         1.至少一位数字，后面跟着一个点 '.'
//         2.至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
//         3.一个点 '.' ，后面跟着至少一位数字

// 整数（按顺序）可以分成以下几个部分：
//     1.（可选）一个符号字符（'+' 或 '-'）
//     2.至少一位数字

// 部分数值列举如下：
// ["+100", "5e2", "-123", "3.1416", "-1E-16", "0123"]
// 部分非数值列举如下：
// ["12e", "1a3.14", "1.2.3", "+-5", "12e+5.4"]
 
// 示例 1：
// 输入：s = "0"
// 输出：true

// 示例 2：
// 输入：s = "e"
// 输出：false

// 示例 3：
// 输入：s = "."
// 输出：false

// 示例 4：
// 输入：s = "    .1  "
// 输出：true

// 提示：
// 1 <= s.length <= 20
// s 仅含英文字母（大写和小写），数字（0-9），加号 '+' ，减号 '-' ，空格 ' ' 或者点 '.' 。

// -------------------第三次刷-----------------------
// 2021年5月12日11:38:45
// 准备第一次社招
// 思路: 由5个部分组成. 分别是[+-整数块1, 小数点, 整数块2, eE, +-整数块3], 有小数点的时候整数块1和整数块2必须至少存在一个, 有eE的时候, 整数块3必须存在.
// 注意: 整数块1和整数块3都可以是正负的
// 注意: leetcode比剑指offer多允许了头尾的空格
// 注意: 需要稍微注意一下最后返回的时候写法
// 注意: flag = flag1 || fun(); //如果flag为true, 则fun()不执行, flag直接为true

#include <string>
using namespace std;

class Solution {
public:
    void skip(string s, int& index){
        while(s[index]==' ')
            index++;
    }

    bool isInters(string s, int& index){
        int temp = index;
        while(s[index]>='0'&&s[index]<='9'&&index<s.size())
            index++;
        return temp != index;
    }

    bool isNumber(string s) {
        if(s.size() == 0)
            return false;
        int index = 0;
        skip(s, index);

        //+-
        if(s[index]=='+'||s[index]=='-')
            index++;
        //整数块1
        bool flag = isInters(s, index);
        //小数点
        if(s[index] == '.'){
            index++;
            //整数块2
            flag = isInters(s, index) || flag;
        }
        //eE
        if(s[index] == 'e' || s[index] == 'E'){
            index++;

            //+-
            if(s[index]=='+'||s[index]=='-')
                index++;
            //整数块3
            flag = flag && isInters(s, index);
        }

        skip(s, index);
        return flag && index==s.size();
    }
};

//page 127
class Solution
{
public:
    // bool isNumeric(char *string)
    // {
    //     if (string == nullptr)
    //         return false;

    //     if (*string == '+' || *string == '-')
    //         string++;
    //     while (*string != '\0' && *string <= '9' && *string >= '0')
    //         string++;
    //     if (*string == '\0')
    //         return true;
    //     else if (*string == '.' || *string == 'E' || *string == 'e')
    //         ;
    //     else
    //         return false;

    //     if (*string == '.')
    //     {
    //         string++;
    //         while (*string != '\0' && *string <= '9' && *string >= '0')
    //             string++;
    //         if (*string == '\0')
    //             return true;
    //         else if (*string == 'E' || *string == 'e')
    //             ;
    //         else
    //             return false;
    //     }

    //     if (*string == 'E' || *string == 'e')
    //     {
    //         string++;
    //         if (*string == '\0')
    //             return false;
    //         if (*string == '+' || *string == '-')
    //             string++;
    //         while (*string != '\0' && *string <= '9' && *string >= '0')
    //             string++;
    //         if (*string == '\0')
    //             return true;
    //         else
    //             return false;
    //     }
    // }
    // bool isNumeric(char *string)
    // {
    //     if (*string == '+' || *string == '-')
    //         string++;

    //     //is_number
    //     bool flag_1 = false;
    //     while (*string >= '0' && *string <= '9')
    //     {
    //         string++;
    //         flag_1 = true;
    //     }

    //     if (*string == '.')
    //     {
    //         string++;
    //         bool flag_2 = false;
    //         while (*string >= '0' && *string <= '9')
    //         {
    //             string++;
    //             flag_2 = true;
    //         }
    //         if ((*string == 'e' || *string == 'E') && flag_2 == true)
    //         {

    //             string++;
    //             if (*string == '+' || *string == '-')
    //                 string++;
    //             bool flag_3 = false;
    //             while (*string >= '0' && *string <= '9')
    //             {
    //                 string++;
    //                 flag_3 = true;
    //             }
    //             if (*string == '\0')
    //                 return flag_3;
    //             else
    //                 return false;
    //         }
    //         else if (*string=='\0')
    //         {
    //             return flag_2;
    //         }
    //         else
    //             return false;
    //     }
    //     else if ((*string == 'e' || *string == 'E') && flag_1 == true)
    //     {
    //         string++;
    //         if (*string == '+' || *string == '-')
    //             string++;

    //         bool flag_3 = false;
    //         while (*string >= '0' && *string <= '9')
    //         {
    //             string++;
    //             flag_3 = true;
    //         }
    //         if (*string == '\0')
    //             return flag_3;
    //         else
    //             return false;
    //     }
    //     else if (*string=='\0')
    //     {
    //         return true;
    //     }

    //     else
    //         return false;
    // }

    bool isInter(char *&string)
    {
        char * temp=string;
        while (*string >= '0' && *string <= '9')
        {
            string++;
        }
        return temp!=string;
    }

    bool isNumeric(char *string)
    {
        if (string == nullptr)
            return false;

        if (*string == '+' || *string == '-')
            string++;
        bool flag_inter1 = isInter(string);
        
        if(*string == '.')
        {
            string++;            
            //小数点两边必须至少存在一个
            flag_inter1 = isInter(string)||flag_inter1;
        }     

        if (*string=='e'||*string=='E')
        {
            string++;
            if (*string == '+' || *string == '-')
                string++;
            //出现e之后必须保证e的两边都存在
            flag_inter1 = isInter(string)&&flag_inter1;
        }
        //必须最后一个是'\0'
        return *string=='\0'&&flag_inter1;
        
    }
};

int main()
{
    char string[] = "+.12";
    Solution solution;
    bool result = solution.isNumeric(string);
    return 0;
}
