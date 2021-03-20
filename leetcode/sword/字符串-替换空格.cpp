//page 51
#include <iostream>

// void replaceSpace(char *str, int length)
// {
//     if (str == nullptr || length <= 0)
//         return;

//     int i = 0;
//     int num_blank = 0;
//     int length_original = 0;
//     while (str[i] != '\0')
//     {
//         if (str[i] == ' ')
//             num_blank++;
//         i++;
//         length_original++;
//     }

//     int length_new = length_original + 2 * num_blank;
//     if (length_new > length)
//         return;

//     int index_original= length_original;
//     int index_new = length_new;
//     while(index_original >= 0)
//     {
//         if(str[index_original]==' ')
//         {
//             str[index_new--] = '0';
//             str[index_new--] = '2';
//             str[index_new--] = '%';
//         }
//         else
//         {
//             str[index_new--] = str[index_original];
//         }
//         index_original--;

//     }
// }

class Solution
{
public:
    void replaceSpace(char *str, int length)
    {
        if (str == nullptr || length < 0)
            return;

        int num_blank = 0;
        int num_original = 0;
        char *p1 = str;
        while (*p1 != '\0')
        {
            if (*p1 == ' ')
                num_blank++;
            num_original++;
            p1++;
        }
        num_original++;
        if (num_original + 2 * num_blank  > length)
            return;

        
        char *p2 = p1 + 2 * num_blank;
        //结束条件是两者相遇
        while(p1!=p2)
        {
            if(*p1==' ')
            {
                *p2='0';
                p2--;
                *p2='2';
                p2--;
                *p2='%';
            }
            else
            {
                *p2 = *p1;
            }                        
            p1--;
            p2--;
        }
    }
};

int main()
{
    char str[]="Hello World";

    Solution solution;
    solution.replaceSpace(str,50);
    return 0;
}