#include <string>
#include <utility>
#include <stack>
using namespace std;

// 烦死了, fuck, 还不能调试

// 394. 字符串解码
// 给定一个经过编码的字符串，返回它解码后的字符串。
// 编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。
// 你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。
// 此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

// 示例 1：
// 输入：s = "3[a]2[bc]"
// 输出："aaabcbc"

// 示例 2：
// 输入：s = "3[a2[c]]"
// 输出："accaccacc"

// 示例 3：
// 输入：s = "2[abc]3[cd]ef"
// 输出："abcabccdcdcdef"

// 示例 4：
// 输入：s = "abc3[cd]xyz"
// 输出："abccdcdcdxyz"

// -------------------第二次刷-----------------------
// 2021年7月12日10:34:30
// 准备第一次社招
// 思路: 后遇到的先处理与栈的机制类似, 因此用一个辅助栈. 用一个pair, first保存重复次数, second保存两个[之间的字符串a, 两边也可以认为是有两个[]的. 这个字符串是用来作为拼接的前部分. 怎么得到这个字符串,
// 一方面是遇到字符串后加在后面, 另一方面是每次重复后添加后. 遇到[后添加pair并且清空这两个变量.  

string decodeString(string s) {
	//两个栈分别压int res和用pair
	stack<pair<int, string>> sta;
	int num = 0; string res = "";
	//循环检查字符串
	for (int i = 0; i < s.size(); i++) {
		//遇到数字则存入num
		if (s[i] >= '0'&&s[i] <= '9') {//数字可能大于10
			num *= 10;
			num += (s[i] - '0');//这里括号是否需要
		}
		else if (s[i] == '[') {//遇到[压栈数字和字符串，置零置空
			sta.push(make_pair(num, res));
			num = 0;
			res = "";
		}
		else if (s[i] == ']') {//遇到]出栈数字和字符串，组装
			int n = sta.top().first;//n指示的是res的循环次数，不是a的
			string a = sta.top().second;
			sta.pop();
			for (int i = 0; i < n; i++)  
                a = a + res; //循环n次
			res = a;
		}
		else {//遇到字符存入字符
			res += s[i];
		}		
	}
	return res;
}

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
