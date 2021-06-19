#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 22. 括号生成
// 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

// 示例 1：
// 输入：n = 3
// 输出：["((()))","(()())","(())()","()(())","()()()"]

// 示例 2：
// 输入：n = 1
// 输出：["()"]

// -------------------第二次刷-----------------------
// 2021年6月9日10:45:22
// 准备第一次社招
// 思路:
// 回溯法
// 如果左括号数量不大于 n，我们可以放一个左括号。如果右括号数量小于左括号的数量，我们可以放一个右括号
class Solution {
public:
    void generateParenthesis_repeat(vector<string>& result, string& str, int n, int left, int right) {
        if (left == n && right == n) {
            result.push_back(str);
            return;
        }

        if (left < n) {
            str.push_back('(');
            generateParenthesis_repeat(result, str, n, left + 1, right);
            str.pop_back();
        }
        if (right < left) {
            str.push_back(')');
            generateParenthesis_repeat(result, str, n, left, right + 1);
            str.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string str;
        generateParenthesis_repeat(result, str, n, 0, 0);
        return result;
    }
};