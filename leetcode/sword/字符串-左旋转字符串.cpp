//page 286
#include <string>

using namespace std;

class Solution
{
public:
    // string LeftRotateString(string str, int n)
    // {
    //     if(str.size()==0)
    //         return str;
    //     if (n > str.size())
    //     {
    //         n %= str.size();
    //     }
    //     string s_new(str.begin() + n, str.end());
    //     string s_add(str.begin(), str.begin() + n);
    //     s_new += s_add;
    //     return s_new;
    // }
    string LeftRotateString(string str, int n)
    {
        if (n > str.size())
            n %= str.size();
        if (n <= 0)
            return str;

        string s(str.begin(), str.begin() + n);
        str.erase(0, n);
        str += s;
        return str;
    }
};

int main()
{
    Solution solution;
    string s = "abcXYZdef";
    int n = 13;
    solution.LeftRotateString(s, n);
    return 0;
}