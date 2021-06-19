#include <string>
#include <vector>

using namespace std;

// 5. 最长回文子串
// 给你一个字符串 s，找到 s 中最长的回文子串。

// 示例 1：
// 输入：s = "babad"
// 输出："bab"
// 解释："aba" 同样是符合题意的答案。

// 示例 2：
// 输入：s = "cbbd"
// 输出："bb"

// 示例 3：
// 输入：s = "a"
// 输出："a"

// 示例 4：
// 输入：s = "ac"
// 输出："a"
 
// 提示：
// 1 <= s.length <= 1000
// s 仅由数字和英文字母（大写和/或小写）组成

// -------------------第二次刷-----------------------
// 2021年6月7日16:12:04
// 准备第一次社招
// 思路1: 中心向两端扩散的思路. 注意回文子串不一定是奇数, 也可能是偶数

// 思路2: 因为有递推关系, 所以也可以考虑动态规划. dp[i][j]表示从索引i为起始, 终点索引为j的子串是否是. 注意这里先两层循环先是长度, 因为长子串结果依赖于短子串
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));
        string ans;
        for (int l = 0; l < n; ++l) {//从0开始遍历长度l
            for (int i = 0; i + l < n; ++i) {//从0开始遍历起始位置i
                int j = i + l;
                if (l == 0) {
                    dp[i][j] = 1;//长度为0时就是单个字母,属于回文
                } else if (l == 1) {//长度为1代表两个字母
                    dp[i][j] = (s[i] == s[j]);
                } else {
                    dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);
                }
                if (dp[i][j] && l + 1 > ans.size()) {
                    ans = s.substr(i, l + 1);
                }
            }
        }
        return ans;
    }
};