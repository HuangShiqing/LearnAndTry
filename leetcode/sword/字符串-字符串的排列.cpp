// 剑指 Offer 38. 字符串的排列
// 输入一个字符串，打印出该字符串中字符的所有排列。

// 你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。

// 示例:
// 输入：s = "abc"
// 输出：["abc","acb","bac","bca","cab","cba"]

// 2021年05月17日22:13:53
// 准备第一次社招
// 思路: 递归, 而且不需要删除一个字符然后又插入一个字符, 只需要swap即可
// 注意: 可能有相同字符造成结果重复, 返回前要去重
#include <vector>
using namespace std;

class Solution {
public:
    void permutation(vector<string>& vv, string s_temp, string s, int index) {
        if(index==s.size()){
            vv.push_back(s_temp);
        }

        for(int i=index;i<s.size();i++){
            s_temp += s[i];
            swap(s[index], s[i]);
            permutation(vv, s_temp, s, index+1);
            swap(s[index], s[i]);
            s_temp.pop_back();
        }
    }

    vector<string> permutation(string s) {
        vector<string>  vv;
        string s_temp;
        if(s.size()==0)
            return vv;
        permutation(vv, s_temp, s, 0);

        sort(vv.begin(), vv.end());
        vector<string>::iterator new_end = unique(vv.begin(), vv.end());
        vector<string> vv_uniqued(vv.begin(),new_end);
        return vv_uniqued;
    }
};

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    string middle;
    vector<string> final_result;
    void Permutation_repeat(string str)
    {
        if (str.size() == 1)
        {
            middle += str;
            final_result.push_back(middle);
            middle.pop_back();
            return;
        }
        else
        {
            for (int i = 0; i < str.size(); i++)
            {
                middle += str[i];
                // if (!middle.find(str[i]))
                // {
                swap(str[0], str[i]);
                string new_string(str, 1);
                Permutation_repeat(new_string);
                swap(str[0], str[i]);
                // }
                middle.pop_back();
            }
        }
    }

    vector<string> Permutation(string str)
    {
        Permutation_repeat(str);
        sort(final_result.begin(), final_result.end());
        vector<string>::iterator new_end = unique(final_result.begin(), final_result.end());
        vector<string> final_result_uniqued(final_result.begin(),new_end);
        return final_result_uniqued;
    }
};