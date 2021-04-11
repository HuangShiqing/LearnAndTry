#include <iostream>
#include <vector>
using namespace std;

//"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"
// ["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"]
// 不带记忆的回朔法会超时

class Solution {
public:
    bool compare_(string s, int index, string word) {
        for (int i = 0; i < word.size(); i++) {
            if (s[index + i] != word[i])
                return false;
        }
        return true;
    }

    bool wordBreak_repeat(string s, vector<string>& wordDict, vector<bool>& map, int index) {
        if (index == s.size())
            return true;
        if (map[index] != true)
            return false;

        for (int i = 0; i < wordDict.size(); i++) {
            if (compare_(s, index, wordDict[i]))
                if (wordBreak_repeat(s, wordDict, map, index + wordDict[i].size()))
                    return true;
        }
        map[index] = false;

        return false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> map(s.size(), true);  //这里的记忆是"map[index]代表s[index:]能否有可能被完全拆分
        return wordBreak_repeat(s, wordDict, map, 0);
    }
};