// Page 88
#include <string.h>

#include <iostream>
using namespace std;

class Solution {
public:
    // char *gpch_matrix = nullptr;
    // char *gpch_str = nullptr;
    // int gi_rows=0;
    // int gi_cols=0;
    // int gi_length = 0;

    // bool hasPath_repeat(int row, int col, bool *visited)
    // {
    //     if (gpch_str[gi_length] == '\0')
    //         return true;
    //     bool result = false;
    //     if (row >= 0 && row < gi_rows && col >= 0 && col < gi_cols && gpch_matrix[gi_cols * row + col] ==
    //     gpch_str[gi_length] && visited[gi_cols * row + col] != true)
    //     {
    //         gi_length++;
    //         visited[gi_cols * row + col] = true;

    //         result = hasPath_repeat(row + 1, col, visited) || hasPath_repeat(row - 1, col, visited) ||
    //         hasPath_repeat(row, col + 1, visited) || hasPath_repeat(row, col - 1, visited);

    //         if (result == false)
    //         {
    //             gi_length--;
    //             visited[gi_cols * row + col] = false;
    //         }
    //     }

    //     return result;
    // }

    // bool hasPath(char *matrix, int rows, int cols, char *str)
    // {
    //     if (matrix == nullptr || rows <= 0 || cols <= 0 || str == nullptr)
    //         return false;

    //     gi_rows = rows;
    //     gi_cols = cols;
    //     gpch_matrix = matrix;
    //     gpch_str = str;

    //     bool *visited = new bool[rows * cols];
    //     memset(visited, 0, rows * cols * sizeof(bool));

    //     for (int i = 0; i < rows; i++)
    //     {
    //         for (int j = 0; j < cols; j++)
    //         {
    //             if (hasPath_repeat(i, j, visited))
    //                 return true;
    //         }
    //     }
    //     return false;
    // }
    char* g_matrix = nullptr;
    char* g_str = nullptr;
    bool* g_map = nullptr;
    int g_index = 0;
    int g_rows;
    int g_cols;

    //函数的返回代表当前选择路径上能否走到最终满足要求
    bool hasPath_repeat(int row, int col) {
        //非法情况退出
        if (row < 0 || row >= g_rows || col < 0 || col >= g_cols || g_map[row * g_cols + col] == true ||
            g_matrix[row * g_cols + col] != g_str[g_index])
            return false;
        //当前步合法后的一些标记操作
        g_map[row * g_cols + col] = true;
        g_index++;

        //最终步不再需要递归
        if (g_str[g_index] == '\0')
            return true;
        //判断走了当前步后，下一步是否有成功的可能
        if ((hasPath_repeat(row - 1, col) || hasPath_repeat(row + 1, col) || hasPath_repeat(row, col - 1) ||
             hasPath_repeat(row, col + 1)) == false) {
            //如果走了当前步后下一步不论怎么走都没有成功的可能就要取消当前步
            g_index--;
            g_map[row * g_cols + col] = false;
            return false;
        }
        return true;
    }
    bool hasPath(char* matrix, int rows, int cols, char* str) {
        if (matrix == nullptr || str == nullptr || rows <= 0 || cols <= 0)
            return false;

        g_matrix = matrix;
        g_str = str;
        g_rows = rows;
        g_cols = cols;
        g_map = new bool[cols * rows];
        memset(g_map, 0, sizeof(bool) * cols * rows);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (hasPath_repeat(i, j) == true)
                    return true;
            }
        }
        return false;
    }
};

int main() {
    char matrix[] = {"ABCESFCSADEE"};
    int row = 3;
    int col = 4;
    char str[] = {"ABCB"};
    Solution solution;
    bool result = solution.hasPath(matrix, row, col, str);
    return 0;
}

// 剑指 Offer 12. 矩阵中的路径
// 给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。
// 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
// 例如，在下面的 3×4 的矩阵中包含单词 "ABCCED"（单词中的字母已标出）。

// 示例 1：
// 输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
// 输出：true
// 示例 2：
// 输入：board = [["a","b"],["c","d"]], word = "abcd"
// 输出：false

// 2021年04月26日22:53:18
// 准备第一次社招
// 思路:
// 比较简答的带flag的dfs回溯
#include <vector>
using namespace std;
class solution {
public:
    bool in(vector<vector<char>>& board, vector<vector<bool>>& flag, int h, int w) {
        if (h < 0 || h > board.size() - 1)
            return false;
        if (w < 0 || w > board[0].size() - 1)
            return false;
        if (flag[h][w] == false)
            return false;
        return true;
    }

    bool exist_repeat(vector<vector<char>>& board, vector<vector<bool>>& flag, string word, int index, int h, int w) {
        // 遍历到最后完成任务退出
        if (index > word.size() - 1)
            return true;
        // 超出棋盘边界退出
        if (!in(board, flag, h, w)) {
            return false;
        }
        // 当前位置不满足进入条件退出
        if (board[h][w] != word[index])
            return false;
        
        flag[h][w] = false; //标记
        if (exist_repeat(board, flag, word, index + 1, h + 1, w))
            return true;
        if (exist_repeat(board, flag, word, index + 1, h - 1, w))
            return true;
        if (exist_repeat(board, flag, word, index + 1, h, w + 1))
            return true;
        if (exist_repeat(board, flag, word, index + 1, h, w - 1))
            return true;
        flag[h][w] = true;//失败退出前记得回溯
        return false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        vector<vector<bool>> flag(board.size(), vector<bool>(board[0].size(), true));

        for (int h = 0; h < board.size(); h++) {
            for (int w = 0; w < board[0].size(); w++) {
                if (exist_repeat(board, flag, word, 0, h, w))
                    return true;
            }
        }
        return false;
    }
};