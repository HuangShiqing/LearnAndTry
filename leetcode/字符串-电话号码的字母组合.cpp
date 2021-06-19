// 17. 电话号码的字母组合
// 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
// 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

// 示例 1：
// 输入：digits = "23"
// 输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]

// 示例 2：
// 输入：digits = ""
// 输出：[]

// 示例 3：
// 输入：digits = "2"
// 输出：["a","b","c"]

// -------------------第二次刷-----------------------
// 2021年6月8日15:55:01
// 准备第一次社招
// 思路: 回溯即可. 不知道为什么leetcode会直接报错

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    void DFS(string& digits, int index, string& str, vector<string>& result, unordered_map<char, string>& phoneMap) {
        if (index == digits.size()) {
            result.push_back(str);
            return;
        }

        string ss = phoneMap[digits[index]];
        for (const char& s : ss) {
            str += s;
            DFS(digits, index + 1, str, result, phoneMap);
            str.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        vector<string> result;
        string str;
        unordered_map<char, string> phoneMap{{'2', "abc"}, {'3', "def"},  {'4', "ghi"}, {'5', "jkl"},
                                             {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};

        if (digits.size() == 0)
            return result;

        DFS(digits, 0, str, result, phoneMap);
        return result;
    }
};

int main() {
    Solution s;
    s.letterCombinations("23");
    return 0;
}