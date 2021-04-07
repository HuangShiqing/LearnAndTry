#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 回溯法
// 如果左括号数量不大于 nn，我们可以放一个左括号。如果右括号数量小于左括号的数量，我们可以放一个右括号
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