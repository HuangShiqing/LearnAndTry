#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 79. 单词搜索
// 给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。
// 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

// 示例 1：
// 输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
// 输出：true

// 示例 2：
// 输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
// 输出：true

// 示例 3：
// 输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
// 输出：false

// -------------------第二次刷-----------------------
// 2021年6月11日10:46:00
// 准备第一次社招
// 思路: 带记忆的递归

class Solution {
public:
    bool exist_repeat(vector<vector<char>>& board, vector<vector<bool>>& flag, string& word, int word_index,
                      int i_index, int j_index) {
        if(i_index + 1 >= board.size()||i_index - 1 < 0||j_index + 1 >= board[0].size()||j_index - 1 < 0)
            return false;
        if (board[i_index][j_index] != word[word_index])
            return false;
        if (word_index == word.size() - 1)
            return true;
            

        if (flag[i_index + 1][j_index] != false) {
            flag[i_index + 1][j_index] = false;
            if (exist_repeat(board, flag, word, word_index + 1, i_index + 1, j_index))
                return true;
            flag[i_index + 1][j_index] = true;
        }

        if (flag[i_index - 1][j_index] != false) {
            flag[i_index - 1][j_index] = false;
            if (exist_repeat(board, flag, word, word_index + 1, i_index - 1, j_index))
                return true;
            flag[i_index - 1][j_index] = true;
        }

        if (flag[i_index][j_index + 1] != false) {
            flag[i_index][j_index + 1] = false;
            if (exist_repeat(board, flag, word, word_index + 1, i_index, j_index + 1))
                return true;
            flag[i_index][j_index + 1] = true;
        }

        if (flag[i_index][j_index - 1] != false) {
            flag[i_index][j_index - 1] = false;
            if (exist_repeat(board, flag, word, word_index + 1, i_index, j_index - 1))
                return true;
            flag[i_index][j_index - 1] = true;
        }

        return false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        vector<vector<bool>> flag(board.size(), vector<bool>(board[0].size(), true));  //初始化指定大小的二维v
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                flag[i][j] = false;
                if (exist_repeat(board, flag, word, 0, i, j))
                    return true;
                flag[i][j] = true;
            }
        }
        return false;
    }
};