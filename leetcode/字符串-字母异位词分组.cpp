#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;


// 49. 字母异位词分组
// 给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。

// 示例:
// 输入: ["eat", "tea", "tan", "ate", "nat", "bat"]
// 输出:
// [
//   ["ate","eat","tea"],
//   ["nat","tan"],
//   ["bat"]
// ]

// 说明：
// 所有输入均为小写字母。
// 不考虑答案输出的顺序。

// -------------------第二次刷-----------------------
// 2021年6月10日10:30:53
// 准备第一次社招
// 思路: 给字符串重新排序, 那么所有异位词都变成一样的了, 可将排序后的作为key, 排序前的作为value vector中的一个

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> map;
        for (string& str : strs) {
            string key = str;
            sort(key.begin(), key.end());//排序后为一样
            map[key].push_back(str);
        }
        vector<vector<string>> result;
        for (auto it = map.begin(); it != map.end(); it++) {
            result.push_back(it->second);
        }
        return result;
    }
};