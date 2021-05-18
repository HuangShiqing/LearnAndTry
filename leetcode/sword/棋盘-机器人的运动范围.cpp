#include <string.h>

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    // int gc_count = 0;
    // int gi_threshold = 0;
    // int gi_rows = 0;
    // int gi_cols = 0;
    // bool *gpb_map = nullptr;

    // void movingCount_repeat(int row, int col)
    // {
    //     if (row >= 0 && row < gi_rows && col >= 0 && col < gi_cols && gpb_map[row * gi_cols + col] == false)
    //     {
    //         string s1 = to_string(row);
    //         string s2 = to_string(col);
    //         int num1 = 0;
    //         int num2 = 0;
    //         char *temp_num = new char[s1.size()];
    //         for (int i = 0; i < s1.size(); i++)
    //         {
    //             strcpy(temp_num, s1.c_str());
    //             num1 += (s1[i] - '0');
    //         }
    //         for (int i = 0; i < s2.size(); i++)
    //         {
    //             strcpy(temp_num, s2.c_str());
    //             num2 += (s2[i] - '0');
    //         }

    //         // bool result = false;
    //         if (num1 + num2 <= gi_threshold)
    //         {
    //             gpb_map[row * gi_cols + col] = true;
    //             movingCount_repeat(row + 1, col);
    //             movingCount_repeat(row - 1, col);
    //             movingCount_repeat(row, col + 1);
    //             movingCount_repeat(row, col - 1);
    //         }
    //     }
    // }

    // int movingCount(int threshold, int rows, int cols)
    // {
    //     if (rows <= 0 || cols <= 0||threshold <= 0)
    //         return 0;
    //     // if (threshold <= 0)
    //     //     return rows * cols;

    //     bool *map = new bool[rows * cols];
    //     memset(map, 0, rows * cols * sizeof(bool));
    //     gpb_map = map;
    //     gi_threshold = threshold;
    //     gi_rows = rows;
    //     gi_cols = cols;

    //     movingCount_repeat(0, 0);
    //     int num = 0;
    //     for (int i = 0; i < rows * cols; i++)
    //     {
    //         if (map[i] == true)
    //             num += 1;
    //     }
    //     return num;
    // }
    bool* map = nullptr;
    int g_threshold;
    int g_rows;
    int g_cols;
    int g_count = 0;
    void movingCount_repeat(int rows, int cols) {
        if (rows < 0 || cols < 0 || rows >= g_rows || cols >= g_cols || map[rows * g_cols + cols] == true)
            return;

        string s1 = to_string(rows);
        string s2 = to_string(cols);
        string s3 = s1 + s2;
        int num = 0;
        for (int i = 0; i < s3.size(); i++)
            num += s3[i] - '0';
        if (num <= g_threshold) {
            g_count++;
            map[rows * g_cols + cols] = true;
            movingCount_repeat(rows, cols + 1);
            movingCount_repeat(rows, cols - 1);
            movingCount_repeat(rows + 1, cols);
            movingCount_repeat(rows - 1, cols);
        }
    }

    int movingCount(int threshold, int rows, int cols) {
        if (threshold <= 0 || rows <= 0 || cols <= 0)
            return 0;

        map = new bool[rows * cols];
        memset(map, 0, rows * cols * sizeof(bool));
        g_threshold = threshold;
        g_cols = cols;
        g_rows = rows;

        movingCount_repeat(0, 0);
        return g_count;
    }
};

int main() {
    Solution solution;
    int r = solution.movingCount(10, 1, 10);

    return 0;
}

// 剑指 Offer 13. 机器人的运动范围
// 地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。一个机器人从坐标 [0, 0]
// 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。
// 例如，当k为18时，机器人能够进入方格[35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，
// 因为3+5+3+8=19。请问该机器人能够到达多少个格子？

// 示例 1：
// 输入：m = 2, n = 3, k = 1
// 输出：3
// 示例 2：
// 输入：m = 3, n = 1, k = 0
// 输出：1

// 2021年04月25日22:41:25
// 准备第一次社招
// 思路:
// dfs回溯, 跟矩阵中的路径太类似了, 不写了, 就写个退出条件
class Solution {
public:
    bool movingCount_repeat(int h, int w, int k) {
        // ...
        string s1 = to_string(h);
        string s2 = to_string(w);
        string s3 = s1 + s2;
        int num = 0;
        for (int i = 0; i < s3.size(); i++)
            num += s3[i] - '0';
        if (num > k)
            return false;
        // ...
    }
    int movingCount(int m, int n, int k) {

    }
};