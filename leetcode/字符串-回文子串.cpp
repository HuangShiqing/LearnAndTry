#include <string>
using namespace std;

// 647. 回文子串
// 给定一个字符串，你的任务是计算这个字符串中有多少个回文子串。
// 具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

// 示例 1：
// 输入："abc"
// 输出：3
// 解释：三个回文子串: "a", "b", "c"

// 示例 2：
// 输入："aaa"
// 输出：6
// 解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"

// -------------------第二次刷-----------------------
// 2021年7月21日15:49:27
// 准备第一次社招
// 思路: 跟最长回文子串一模一样
// 思路1: 中心向两端扩散的思路. 注意回文子串不一定是奇数, 也可能是偶数
// 思路2: 因为有递推关系, 所以也可以考虑动态规划. dp[i][j]表示从索引i为起始, 终点索引为j的子串是否是. 注意这里先两层循环先是长度, 因为长子串结果依赖于短子串
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    //思路1:
    int countSubstrings(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));
        int ans = 0;
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
                
                if(dp[i][j] == 1)
                    ans++;
            }
        }
        return ans;
    }

    // 思路2:
    // 三层for循环, 第一层是双指针往两头移动, 相等则count++并继续向两头移动直到索引达到临界
    // 第二层是初始索引可以从0到size-1
    // 第三层是初始索引可以指向同一个数或者指向相邻的两个数
    int countSubstrings(string s) {
        int i,j;
        int n = s.size();
        int count=0;
        
        for(int k=0;k<n;k++){  
            i = k;
            j = k;
            while(i>=0&&j<n){ 
                if(s[i]==s[j]){
                    count++;
                    i--;
                    j++;            
                }
                else
                    break;
            }
        }
        for(int k=0;k<n-1;k++){  
            i = k;
            j = k+1;
            while(i>=0&&j<n){      
                if(s[i]==s[j]){
                    count++;
                    i--;
                    j++;            
                }
                else
                    break;
            }
        }

        return count;
            
    }
};