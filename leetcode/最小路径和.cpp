#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 设 dp为大小 m×n 矩阵，其中 dp[i][j]的值代表直到走到 (i,j)的最小路径和
// 1.当左边和上边都不是矩阵边界时： 即当i != 0, j != j 时，dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j]
// 2.当只有左边是矩阵边界时： 只能从上面来，即当i = 0, j != 0,j =0时， dp[i][j] = dp[i][j - 1] + grid[i][j]
// 3.当只有上边是矩阵边界时： 只能从左面来，即当i != 0, j = 0时， dp[i][j] = dp[i - 1][j] + grid[i][j]
// 4.当左边和上边都是矩阵边界时： 即当i = 0, j = 0时，其实就是起点， dp[i][j] = grid[i][j]

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0)
                    dp[i][j] = grid[i][j];
                else if (i == 0)
                    dp[i][j] = dp[i][j - 1] + grid[i][j];
                else if (j == 0)
                    dp[i][j] = dp[i - 1][j] + grid[i][j];
                else
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        return dp[m-1][n-1];
    }
};