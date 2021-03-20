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