#include <iostream>
#include <vector>
using namespace std;

// 139. 单词拆分
// 给定一个非空字符串 s 和一个包含非空单词的列表 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。
// 说明：
// 拆分时可以重复使用字典中的单词。
// 你可以假设字典中没有重复的单词。

// 示例 1：
// 输入: s = "leetcode", wordDict = ["leet", "code"]
// 输出: true
// 解释: 返回 true 因为 "leetcode" 可以被拆分成 "leet code"。

// 示例 2：
// 输入: s = "applepenapple", wordDict = ["apple", "pen"]
// 输出: true
// 解释: 返回 true 因为 "applepenapple" 可以被拆分成 "apple pen apple"。
//      注意你可以重复使用字典中的单词。

// 示例 3：
// 输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
// 输出: false

// -------------------第二次刷-----------------------
// 2021年06月19日09:57:34
// 准备第一次社招
// 思路:
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

// 思路2: dp[i]代表以i结尾的s是否能由wordDict构成
class Solution {
public:
    bool wordBreak(string& s, vector<string>& wordDict) {
        vector<bool> dp(s.size()+1, false);
        dp[0] = true;
        for(int i = 0; i < s.size(); i++){
            if(!dp[i])
                continue;
            for(auto& word : wordDict)
                if(word.size() + i <= s.size() && s.substr(i, word.size()) == word)
                    dp[i+word.size()] = true;
        }
        return dp[s.size()];
    }
};