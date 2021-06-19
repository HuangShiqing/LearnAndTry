#include <algorithm>
#include <vector>
using namespace std;

// 62. 不同路径
// 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
// 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
// 问总共有多少条不同的路径？

// 示例 1：
// 输入：m = 3, n = 7
// 输出：28

// 示例 2：
// 输入：m = 3, n = 2
// 输出：3
// 解释：
// 从左上角开始，总共有 3 条路径可以到达右下角。
// 1. 向右 -> 向下 -> 向下
// 2. 向下 -> 向下 -> 向右
// 3. 向下 -> 向右 -> 向下

// 示例 3：
// 输入：m = 7, n = 3
// 输出：28

// 示例 4：
// 输入：m = 3, n = 3
// 输出：6

// -------------------第二次刷-----------------------
// 2021年6月10日11:42:59
// 准备第一次社招
// 思路: 回溯或者dp

// 回溯遍历耗时太久
// class Solution {
// public:
//     void uniquePaths_repeat(int& local_h, int& local_w, int& target_h, int& target_w, int& num) {
//         if (local_h == target_h && local_w == target_w) {
//             num++;
//             return;
//         }
//         if (local_h < 0 || local_w > target_w)
//             return;

//         local_h--;
//         uniquePaths_repeat(local_h, local_w, target_h, target_w, num);
//         local_h++;

//         local_w++;
//         uniquePaths_repeat(local_h, local_w, target_h, target_w, num);
//         local_w--;
//     }

//     int uniquePaths(int m, int n) {
//         if(m<1||n<1)
//             return 0;

//         int local_h = m-1;//注意要减一
//         int local_w = 0;
//         int target_h = 0;
//         int target_w = n-1;//注意要减一
//         int num = 0;
//         uniquePaths_repeat(local_h, local_w, target_h, target_w, num);

//         return num;
//     }
// };

// 思路一：排列组合
// 因为机器到底右下角，向下几步，向右几步都是固定的，
// 比如，m=3, n=2，我们只要向下 1 步，向右 2 步就一定能到达终点。
// 所以有排列组合C_{m+n-2}^{m-1}

// 思路二：动态规划
// dp[i][j] 是到达 i, j 最多路径,dp[i][j] = dp[i-1][j] + dp[i][j-1]
// 注意，对于第一行 dp[0][j]，或者第一列 dp[i][0]，由于都是在边界且每次移动方向只能是下或者右，所以只能为 1
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
            dp[0][i] = 1;
        for (int i = 0; i < m; i++)
            dp[i][0] = 1;
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
int main() {
    Solution s;
    s.uniquePaths(3, 7);
    return 0;
}