#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    bool exist_repeat(vector<vector<char>>& board, vector<vector<bool>>& flag, string& word, int word_index,
                      int i_index, int j_index) {
        if (board[i_index][j_index] != word[word_index])
            return false;
        if (word_index == word.size() - 1)
            return true;
            

        if (i_index + 1 < board.size()) {
            if (flag[i_index + 1][j_index] != false) {
                flag[i_index + 1][j_index] = false;
                if (exist_repeat(board, flag, word, word_index + 1, i_index + 1, j_index))
                    return true;
                flag[i_index + 1][j_index] = true;
            }
        }
        if (i_index - 1 >= 0) {
            if (flag[i_index - 1][j_index] != false) {
                flag[i_index - 1][j_index] = false;
                if (exist_repeat(board, flag, word, word_index + 1, i_index - 1, j_index))
                    return true;
                flag[i_index - 1][j_index] = true;
            }
        }
        if (j_index + 1 < board[0].size()) {
            if (flag[i_index][j_index + 1] != false) {
                flag[i_index][j_index + 1] = false;
                if (exist_repeat(board, flag, word, word_index + 1, i_index, j_index + 1))
                    return true;
                flag[i_index][j_index + 1] = true;
            }
        }
        if (j_index - 1 >= 0) {
            if (flag[i_index][j_index - 1] != false) {
                flag[i_index][j_index - 1] = false;
                if (exist_repeat(board, flag, word, word_index + 1, i_index, j_index - 1))
                    return true;
                flag[i_index][j_index - 1] = true;
            }
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