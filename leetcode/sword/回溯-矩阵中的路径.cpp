//Page 88
#include <iostream>
#include <string.h>
using namespace std;

class Solution
{
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
    //     if (row >= 0 && row < gi_rows && col >= 0 && col < gi_cols && gpch_matrix[gi_cols * row + col] == gpch_str[gi_length] && visited[gi_cols * row + col] != true)
    //     {
    //         gi_length++;
    //         visited[gi_cols * row + col] = true;

    //         result = hasPath_repeat(row + 1, col, visited) || hasPath_repeat(row - 1, col, visited) || hasPath_repeat(row, col + 1, visited) || hasPath_repeat(row, col - 1, visited);

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
    char *g_matrix = nullptr;
    char *g_str = nullptr;
    bool *g_map = nullptr;
    int g_index = 0;
    int g_rows;
    int g_cols;

    //函数的返回代表当前选择路径上能否走到最终满足要求
    bool hasPath_repeat(int row, int col)
    {
        //非法情况退出
        if (row < 0 || row >= g_rows || col < 0 || col >= g_cols || g_map[row * g_cols + col] == true || g_matrix[row * g_cols + col] != g_str[g_index])
            return false;
        //当前步合法后的一些标记操作
        g_map[row * g_cols + col] = true;
        g_index++;

        //最终步不再需要递归
        if (g_str[g_index] == '\0')
            return true;
        //判断走了当前步后，下一步是否有成功的可能
        if((hasPath_repeat(row - 1, col) || hasPath_repeat(row + 1, col) || hasPath_repeat(row, col - 1) || hasPath_repeat(row, col + 1))==false)
        {
            //如果走了当前步后下一步不论怎么走都没有成功的可能就要取消当前步
            g_index--;
            g_map[row * g_cols + col] = false;
            return false;
        }
        return true;
    }
    bool hasPath(char *matrix, int rows, int cols, char *str)
    {
        if (matrix == nullptr || str == nullptr || rows <= 0 || cols <= 0)
            return false;

        g_matrix = matrix;
        g_str = str;
        g_rows = rows;
        g_cols = cols;
        g_map = new bool[cols * rows];
        memset(g_map, 0, sizeof(bool) * cols * rows);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (hasPath_repeat(i, j) == true)
                    return true;
            }
        }
        return false;
    }
};

int main()
{
    char matrix[] = {"ABCESFCSADEE"};
    int row = 3;
    int col = 4;
    char str[] = {"ABCB"};
    Solution solution;
    bool result = solution.hasPath(matrix, row, col, str);
    return 0;
}