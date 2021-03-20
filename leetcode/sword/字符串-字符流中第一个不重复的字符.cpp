//page 247
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class Solution
{
public:
    //Insert one char from stringstream
    // unordered_map<char, int> map;
    // string s;

    // void Insert(char ch)
    // {
    //     s += ch;
    //     if (map.find(ch) == map.end())
    //     {
    //         map[ch] = 1;
    //     }
    //     else
    //     {
    //         map[ch] += 1;
    //     }
    // }
    // //return the first appearence once char in current stringstream
    // char FirstAppearingOnce()
    // {
    //     for (int i = 0; i < s.size(); i++)
    //     {
    //         if (map[s[i]] == 1)
    //             return s[i];
    //     }
    //     return '#';
    // }
    string g_s;
    unordered_map<char, int> map;
    void Insert(char ch)
    {
        if (map.find(ch) == map.end())
            map[ch] = 1;
        else
            map[ch] += 1;
        g_s += ch;
    }
    char FirstAppearingOnce()
    {
        for (int i = 0; i < g_s.size(); i++)
        {
            if (map[g_s[i]] == 1)
                return g_s[i];
        }
        return '#';
    }
};