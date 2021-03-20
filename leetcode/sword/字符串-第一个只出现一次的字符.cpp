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