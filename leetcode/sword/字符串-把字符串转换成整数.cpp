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