// 438. 找到字符串中所有字母异位词
// 给定一个字符串 s 和一个非空字符串 p，找到 s 中所有是 p 的字母异位词的子串，返回这些子串的起始索引。
// 字符串只包含小写英文字母，并且字符串 s 和 p 的长度都不超过 20100。

// 说明：
// 字母异位词指字母相同，但排列不同的字符串。
// 不考虑答案输出的顺序。

// 示例 1:
// 输入:
// s: "cbaebabacd" p: "abc"
// 输出:
// [0, 6]
// 解释:
// 起始索引等于 0 的子串是 "cba", 它是 "abc" 的字母异位词。
// 起始索引等于 6 的子串是 "bac", 它是 "abc" 的字母异位词。

//  示例 2:
// 输入:
// s: "abab" p: "ab"
// 输出:
// [0, 1, 2]
// 解释:
// 起始索引等于 0 的子串是 "ab", 它是 "ab" 的字母异位词。
// 起始索引等于 1 的子串是 "ba", 它是 "ab" 的字母异位词。
// 起始索引等于 2 的子串是 "ab", 它是 "ab" 的字母异位词。

// -------------------第二次刷-----------------------
// 2021年7月16日14:30:36
// 准备第一次社招
// 思路: 还是从最简单的滑动窗口思路出发. 比较两个窗口是否是字母异位词的话可以用map来保存两个窗口的<char, int>, 分别对应字母和出现的数量.
// 只要map相等, 则为字母异位词. 需要注意的是要手动将一些减小为0的key用erase删除. 如果每次都直接比较两个窗口的map会有点慢, 可以先检查
// 右指针新指向的字符是否在p_map中, 这个find是O(1), 如果不在则直接将left设置为该right+1

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        if (p.size() > s.size()) {            
            return res;
        }

        unordered_map<char, int> s_map;
        unordered_map<char, int> p_map;
        for (int i = 0; i < p.size(); i++) {
            p_map[p[i]]++;
        }
        if(p_map==s_map)
            res.push_back(0);

        int left=0;//当前窗口的left, 实心
        int right=0;//当前窗口的right, 实心        
        while(right<s.size()){
            s_map[s[right]]++;
            if(right-left+1<p.size()){
                right++;
                continue;
            }                
            else if(right-left+1>p.size()){
                s_map[s[left]]--;
                if(s_map[s[left]]==0)
                    s_map.erase(s[left]);
                left++;
            }
            
            if(p_map.find(s[right])!=p_map.end()){
                if(p_map==s_map)
                    res.push_back(left);
                right++;                
            }
            else{
                right++;
                left = right;
                s_map.clear();
            }
            
        }
        return res;
    }
};