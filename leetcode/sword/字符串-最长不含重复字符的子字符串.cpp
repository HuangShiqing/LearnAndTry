// 剑指 Offer 48. 最长不含重复字符的子字符串
// 请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。

// 示例 1:
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
// 解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
//      请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

// -------------------第三次刷-----------------------
// 2021年5月31日10:56:00
// 准备第一次社招
// 思路: 双指针+map. 逐步移动right, 遇到在map里没有的, 则增加map, 更新length与right. 遇到map里有的, 则更新left. 精华是这个max. 保证left不会往前退. 往前退是可能出现重复的
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> map;
        int left = 0;
        int right = 0;
        int max_length = 0;
        while (right < s.size()) {
            if (map.find(s[right]) != map.end()) {  //有
                left = max(left, map[s[right]]+1);// abba, 进入循环时right=3, left=2, 执行到改行时, 如果没有max, 则left回退为1, 因为1-3之间是有重复的2个b的. 因此left不能回退
            }
            map[s[right]] = right;            
            max_length = max(max_length, right - left + 1);
            right++;
        }
        return max_length;
    }
};

int main(){
    Solution s;
    s.lengthOfLongestSubstring("abcabcbb");
    return 0;
}