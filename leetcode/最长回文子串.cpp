#include <string>
#include <vector>

using namespace std;

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