// 剑指 Offer 60. n个骰子的点数
// 把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s的所有可能的值出现的概率。

// 你需要用一个浮点数数组返回答案，其中第 i 个元素代表这 n 个骰子所能掷出的点数集合中第 i 小的那个的概率。

// 示例 1:
// 输入: 1
// 输出: [0.16667,0.16667,0.16667,0.16667,0.16667,0.16667]

// 示例 2:
// 输入: 2
// 输出: [0.02778,0.05556,0.08333,0.11111,0.13889,0.16667,0.13889,0.11111,0.08333,0.05556,0.02778]

// -------------------第三次刷-----------------------
// 2021年6月3日14:30:29
// 准备第一次社招
// 思路: dp[i][j]表示投掷i枚骰子得到点数和为j的次数. 而状态转移方程为为:
// i枚点数和只能是少一枚i-1的点数和+1~6, 即dp[i][j] = dp[i-1][j-1]+dp[i-1][j-2]+dp[i-1][j-3]+dp[i-1][j-4]+dp[i-1][j-5]+dp[i-1][j-6]
// 初始状态dp[1][j]都为1, 其中j为1~6

#include <vector>
#include <math.h>
using namespace std;

class Solution {
public:
    vector<double> dicesProbability(int n) {
        vector<vector<int>> dp(n+1, vector<int>(6*n+1, 0));
        for(int i=1;i<=6;i++)
            dp[1][i] = 1;

        for(int i=2;i<=n;i++){
            for(int j=i;j<=6*i;j++){//点数和最小是当i个骰子全是1, 为i. 点数和最大是当i个骰子全是6, 为6*i
                // dp[i][j] = dp[i-1][j-1]+dp[i-1][j-2]+dp[i-1][j-3]+dp[i-1][j-4]+dp[i-1][j-5]+dp[i-1][j-6]
                for(int k=1;k<=6;k++){
                    if(j-k>=0)
                        dp[i][j] += dp[i-1][j-k];
                }
            }
        }

        int sum = pow(6, n);//投掷n个骰子可能出现的所有的情况
        vector<double> ret;
        for(int i=n;i<=6*n;i++){
            ret.push_back(dp[n][i]/sum);
        }
        return ret;
    }
};

int main(){
    Solution s;
    s.dicesProbability(1);
    return 1;
}