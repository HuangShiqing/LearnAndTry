// 剑指 Offer 58 - II. 左旋转字符串
// 字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。请定义一个函数实现字符串左旋转操作的功能。比如，输入字符串"abcdefg"和数字2，该函数将返回左旋转两位得到的结果"cdefgab"。

// 示例 1：
// 输入: s = "abcdefg", k = 2
// 输出: "cdefgab"

// 示例 2：
// 输入: s = "lrloseumgh", k = 6
// 输出: "umghlrlose"

// -------------------第三次刷-----------------------
// 2021年6月3日10:43:23
// 准备第一次社招
// 思路: 很简单, 可能不会遇到. 就取两段str, 然后倒叙拼接即可
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        string s1 = s.substr(0, n);
        string s2 = s.substr(n, s.size()-n);
        return s2+s1;
    }
};

// 思路2: 这个思路很牛逼. 倍增, 然后从n开始取str
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        s += s;
        return s.substr(n,s.size()/2);
    }
};

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