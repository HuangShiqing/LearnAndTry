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