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