// 剑指 Offer 19. 正则表达式匹配
// 请实现一个函数用来匹配包含'. '和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（含0次）。
// 在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但与"aa.a"和"ab*a"均不匹配。

// 示例 1:
// 输入:
// s = "aa"
// p = "a"
// 输出: false
// 解释: "a" 无法匹配 "aa" 整个字符串。

// 示例 2:
// 输入:
// s = "aa"
// p = "a*"
// 输出: true
// 解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。

// 示例 3:
// 输入:
// s = "ab"
// p = ".*"
// 输出: true
// 解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。

// 示例 4:
// 输入:
// s = "aab"
// p = "c*a*b"
// 输出: true
// 解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。

// 示例 5:
// 输入:
// s = "mississippi"
// p = "mis*is*p*."
// 输出: false
// s 可能为空，且只包含从 a-z 的小写字母。
// p 可能为空，且只包含从 a-z 的小写字母以及字符 . 和 *，无连续的 '*'。

// -------------------第三次刷-----------------------
// 2021年5月11日14:52:37
// 准备第一次社招
// 思路: 字符串逐个操作的应该想到思路就是index+递归. 递归里先写完成退出条件和错误退出条件, 然后根据是否是x*分成两种情况, 是x*又可以分为x*生效0次, 1次, 多次进行递归
// 但是我的退出条件好像一直有问题, shift
#include <string>
using namespace std;

class Solution {
public:
    bool isMatch_repeat(string& s, int index_s, string& p, int index_p){
        if(index_s == s.size() && index_p == p.size())
            return true;
        else if(index_s != s.size() && index_p == p.size())
            return false;
        
        if(p[index_p+1] == '*'){
            if(p[index_p] == s[index_s] || (p[index_p] == '.' && index_s != s.size()))
                return isMatch_repeat(s, index_s, p, index_p+2) || isMatch_repeat(s, index_s+1, p, index_p+2) || isMatch_repeat(s, index_s+1, p, index_p);//0次1次和多次
            else
                return isMatch_repeat(s, index_s, p, index_p+2);
        }
        else {
            if(p[index_p] == '.' || p[index_p] == s[index_s]) 
                return isMatch_repeat(s, index_s+1, p, index_p+1);
            else
                return false;
        }
    }

    bool isMatch(string s, string p) {
        
        return isMatch_repeat(s, 0, p, 0);

    }
};


//page 124
class Solution
{
public:
    // bool match_repeat(char *str, char *pattern)
    // {
    //     if (*str == '\0' && *pattern == '\0')
    //         return true;
    //     if (*str != '\0' && *pattern == '\0')
    //         return false;
    //     //(*str == '\0' && *pattern != '\0')的情况是可能的，比如patter最后是b*，可以是0次

    //     if (*(pattern + 1) != '*')
    //     {
    //         if (*pattern == *str || (*pattern == '.' && *str != '\0'))
    //             //加入*str！=‘\0’是为了防止abc与模式abc.这样的情况出现，这两个是不匹配的。
    //             return match_repeat(str + 1, pattern + 1);
    //         else
    //             return false;
    //     }
    //     else
    //     {
    //         if (*pattern == *str || (*pattern == '.' && *str != '\0'))
    //         //3种情况分别是*前的字母出现0次、1次、多次
    //             return match_repeat(str, pattern + 2)||match_repeat(str + 1, pattern+2)||match_repeat(str + 1, pattern);
    //         else
    //         //如果不相等，可能是出现0次
    //             return match_repeat(str , pattern+2);
    //     }
    // }

    // bool match(char *str, char *pattern)
    // {
    //     if (str == nullptr || pattern == nullptr)
    //         return false;
    //     return match_repeat(str, pattern);
    // }

    // bool match(char *str, char *pattern)
    // {
    //     if (str == nullptr || pattern == nullptr)
    //         return false;
    //     if(*str=='\0'&&*pattern=='\0')
    //         return true;
    //     while ((*str) != '\0' && (*pattern) != '\0')
    //     {
    //         if (*str == *pattern)
    //         {
    //             if (*(pattern + 1) == '*')
    //             {
    //                 if (*(str + 1) == (*pattern))
    //                     str++;
    //                 else
    //                 {
    //                     str++;
    //                     pattern++;
    //                     pattern++;
    //                 }
    //             }
    //             else
    //             {
    //                 str++;
    //                 pattern++;
    //             }
    //         }
    //         else
    //         {
    //             if (*pattern == '.')
    //             {
    //                 str++;
    //                 pattern++;
    //             }
    //             else
    //             {
    //                 if (*(pattern + 1) == '*')
    //                 {
    //                     str++;
    //                     pattern++;
    //                     pattern++;
    //                 }
    //                 else
    //                 {
    //                     return false;
    //                 }
    //             }
    //         }
    //     }
    //     // if(str==nullptr&&pattern==nullptr)
    //     //     return true;
    //     if(*str=='\0'&&*pattern=='\0')
    //         return true;
    //     else if(*str=='\0'&&*pattern!='\0')
    //     {
    //         while(*pattern!='\0')
    //         {
    //             if(*(pattern+1)=='*')
    //                 pattern+=2;
    //             else
    //                 return false;                
    //         }
    //         return true;            
    //     }
    //     else if(*str!='\0'&&*pattern=='\0')
    //         return false;
    // }

    bool match_repeat(char *str, char *pattern)
    {
        if(*str=='\0'&&*pattern=='\0')
            return true;
        
        if(*(pattern+1)!='*')
        {
            if((*pattern=='.'&&*str!='\0')||*str==*pattern)
                return match_repeat(str+1, pattern+1);
            else
                return false;
        }
        else
        {
            if((*pattern=='.'&&*str!='\0')||*str==*pattern)
                return match_repeat(str, pattern+2)||match_repeat(str+1, pattern+2)||match_repeat(str+1, pattern);
            else
                return match_repeat(str, pattern+2);
        }
        
    }

    bool match(char *str, char *pattern)
    {
        if(str==nullptr||pattern==nullptr)
            return false;
        
        return match_repeat(str,pattern);
    }
};

int main()
{
    char str[] = "";
    char pattern[] = ".*";

    Solution solution;
    bool result = solution.match(str, pattern);
    return 0;
}