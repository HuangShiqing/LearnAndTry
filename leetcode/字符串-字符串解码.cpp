#include <string>
using namespace std;

// 烦死了, fuck, 还不能调试

class Solution {
public:
    int todight(int num, char c) {
        num = 10 * num + (c - '0');
        return num;
    }

    string dfs(string s) {
        string r;
        int state = 0;  // 0:正常,1:出现了[
        int sub_start_index;
        int num = 0;
        int left_num = 0;
        for (int i = 0; i < s.size(); i++) {
            if (state == 0) {
                if (s[i] == '[') {
                    if (left_num == 0) {
                        state = 1;
                        sub_start_index = i;
                    }
                    left_num++;

                } else {
                    if (0 <= (s[i] - '0') && 9 >= (s[i] - '0'))
                        num = todight(num, s[i]);
                    else
                        r += s[i];
                }
            } else {
                if (state == 1) {
                    if (s[i] == ']') {
                        if (left_num == 0) 
                        {
                            state = 0;
                            string sub(s, sub_start_index + 1, i - sub_start_index - 1);
                            string rr = dfs(sub);
                            for (int i = 0; i < num; i++)
                                r += rr;
                            num = 0;
                        } 
                        else
                            left_num--;
                    }
                }
            }
        }
        return r;
    }

    string decodeString(string s) {
        string r = dfs(s);
        return r;
    }
};

int main(int argc, char const* argv[]) {
    string a = "3[a]2[bc]";
    Solution s;
    s.decodeString(a);
    return 0;
}
