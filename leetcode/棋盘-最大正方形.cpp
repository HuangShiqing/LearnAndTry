#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 221. 最大正方形
// 在一个由 '0' 和 '1' 组成的二维矩阵内，找到只包含 '1' 的最大正方形，并返回其面积。

// 示例 1：
// 输入：matrix = [["1","0","1","0","0"],
            //    ["1","0","1","1","1"],
            //    ["1","1","1","1","1"],
            //    ["1","0","0","1","0"]]
// 输出：4

// 示例 2：
// 输入：matrix = [["0","1"],
                // ["1","0"]]
// 输出：1

// 示例 3：
// 输入：matrix = [["0"]]
// 输出：0


class Solution {
public:
    // 有点问题的暴力法
    // int maximalSquare(vector<vector<char>>& matrix) {
    //     int w_max = matrix.size();
    //     int h_max = matrix[0].size();
    //     vector<vector<bool>> flag(w_max, vector<bool>(h_max, true));
    //     int size = INT32_MIN;
    //     for (int w = 0; w < w_max; w++) {
    //         for (int h = 0; h < h_max; h++) {
    //             if (matrix[w][h] != '1')
    //                 continue;
    //             for (int i = 1; i < min(w_max - w, h_max - h); i++) {
    //                 bool flag = true;
    //                 for (int k_w = 0; k_w <= i; k_w++) {
    //                     for (int k_h = 0; k_h <= i; k_h++) {
    //                         if (matrix[w + k_w][h + k_h] != '1') {
    //                             flag = false;
    //                             break;
    //                         }
    //                     }
    //                     if (flag == false)
    //                         break;
    //                 }
    //                 if (flag == true)
    //                     size = max(size, i);
    //             }
    //         }
    //     }
    //     return (size+1)*(size+1);
    // }

    // 我们用dp(i,j) 表示以(i,j) 为右下角，且只包含 1 的正方形的边长最大值。如果我们能计算出所有dp(i,j)
    // 的值，那么其中的最大值即为矩阵中只包含 1 的正方形的边长最大值，其平方即为最大正方形的面积 那么如何计算
    // dp 中的每个元素值呢？对于每个位置 (i,j)，检查在矩阵中该位置的值：
    // 1. 如果该位置的值是 0，则 dp(i,j)=0，因为当前位置不可能在由 1 组成的正方形中；
    // 2. 如果该位置的值是 1，则 dp(i,j) 的值由其上方、左方和左上方的三个相邻位置的 dp
    // 值决定。具体而言，当前位置的元素值等于三个相邻位置的元素中的最小值加 1，状态转移方程如下：
    // dp(i, j)=min(dp(i−1, j), dp(i−1, j−1), dp(i, j−1))+1
    // 如果 i 和 j 中至少有一个为 0，则以位置 (i,j) 为右下角的最大正方形的边长只能是 1，因此 dp(i,j)=1

// -------------------第二次刷-----------------------
// 2021年6月28日10:53:31
// 准备第一次社招
// 思路:这里的定义dp[i,j]就不是代表以[0,0]为左上角以该点为右下角的范围内的最大正方形边长了, 而是以该点为右下角的正方形的边长
// 当该点为0时构不成正方形, dp值为0. 当该点为1, 且只有当左上角,上边,左边都不为0时
    int maximalSquare(vector<vector<char>>& matrix) {
        int maxsize = 0;

        int w_max = matrix.size();
        int h_max = matrix[0].size();
        vector<vector<int>> dp(w_max, vector<int>(h_max, 0));
        for (int w = 0; w < w_max; w++) {
            for (int h = 0; h < h_max; h++) {
                if (matrix[w][h] == '1') {
                    if (w == 0 || h == 0)
                        dp[w][h] = 1;
                    else
                        dp[w][h] = min(min(dp[w][h - 1], dp[w - 1][h]), dp[w - 1][h - 1]) + 1;
                    maxsize = max(maxsize, dp[w][h]);
                }
            }
        }
        return maxsize * maxsize;
    }
};