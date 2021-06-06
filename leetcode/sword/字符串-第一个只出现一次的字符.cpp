// 剑指 Offer 50. 第一个只出现一次的字符
// 在字符串 s 中找出第一个只出现一次的字符。如果没有，返回一个单空格。 s 只包含小写字母。

// 示例:
// s = "abaccdeff"
// 返回 "b"
// s = "" 
// 返回 " "


// -------------------第三次刷-----------------------
// 2021年5月31日14:48:44
// 准备第一次社招
// 思路: 很简单, map就行

#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    char firstUniqChar(string s) {
        unordered_map<char, int> map;
        for(int i=0;i<s.size();i++){
            if(map.find(s[i])==map.end()){
                map[s[i]] = 1;
            }
            else{
                // map.erase(s[i]);
                map[s[i]]+=1;
            }
        }

        for(int i=0;i<s.size();i++){
            if(map[s[i]]==1)
                return s[i];
        }
        return ' ';
    }
};

//page 243
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;


class Solution {
public:
    // int FirstNotRepeatingChar(string str) {
        
    //     if(str.size()==0)
    //         return -1;
    //     else if(str.size()==1)
    //         return 0;


    //     unordered_map<char,int> map;
    //     for(int i=0;i<str.size();i++)
    //     {
    //         if(map.find(str[i])==map.end())
    //             map[str[i]]=1;
    //         else
    //             map[str[i]]+=1;
    //     }

    //     unordered_map<char,int>::iterator i;
    //     vector<char> v;
    //     for(i=map.begin();i!=map.end();i++)
    //     {
    //         if(i->second==1)
    //             v.push_back(i->first);
    //     }
    //     if(v.size()==0)
    //         return -1;

    //     int min_num=9999;
    //     int temp;
    //     for(int i=0;i<v.size();i++)
    //     {
    //         temp = str.find(v[i]);
    //         if(temp<min_num)
    //             min_num=temp;
    //     }

    //     return min_num;
    // }
    int FirstNotRepeatingChar(string str)
    {
        unordered_map<char,int> map;
        for(int i=0;i<str.size();i++)
        {
            if(map.find(str[i])==map.end())
                map[str[i]]=1;
            else
                map[str[i]]+=1;            
        }
        for(int i=0;i<str.size();i++)
        {
            if(map[str[i]]==1)
                return i;
        }
        return -1;

    }
};



int main()
{
    string str("googllee");
    Solution solution;
    int result = solution.FirstNotRepeatingChar(str);
}