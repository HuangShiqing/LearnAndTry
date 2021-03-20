#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

// 给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
// 示例 1:
// 输入: "abcabcbb"
// 输出: 3 
// 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
// 示例 2:
// 输入: "bbbbb"
// 输出: 1
// 解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
// 示例 3:
// 输入: "pwwkew"
// 输出: 3
// 解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
//      请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
// 解题思路 https://www.cnblogs.com/mfrank/p/10472651.html
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        //特殊情况就为一个字符
        if(s.size()==1)
            return 1;

        int start = 0;
        int end = 0;
        int length = 1;
        int maxlength = 0;
        while(end<s.size())
        {
            int result = s.substr(start,end-start).find(s[end]);
            if(result != -1)
            {
                length = end - start;//注意，当前end和start是重复的，因此长度是end-start+1-1
                if(length>maxlength)
                    maxlength = length;
                start = start + result + 1;//从第一个重复的的下一个位置开始，result是重复字符在子串的位置因此需要加上start
            }
            end ++;
        }
        return maxlength;
    }
};


int main()
{
    Solution s;
    int a = s.lengthOfLongestSubstring(" ");
    return 0;
}