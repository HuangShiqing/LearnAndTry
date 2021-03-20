//page 284
#include <string>

using namespace std;

class Solution
{
public:
    // string Reverse(string str)
    // {
    //     if (str.size() < 2)
    //         return str;

    //     int start = 0;
    //     int end = str.size() - 1;
    //     while (end > start)
    //     {
    //         swap(str[start], str[end]);
    //         start++;
    //         end--;
    //     }
    //     return str;
    // }

    // string ReverseSentence(string str)
    // {
    //     str = Reverse(str);
    //     string s;

    //     int start = -1, end = 0;
    //     for (int i = 0; i < str.size(); i++)
    //     {
    //         if (str[i] == ' ')
    //         {
    //             end = start + 1;
    //             start = i;
    //             string s_temp(str.begin() + end, str.begin() + start);
    //             s_temp = Reverse(s_temp);
    //             // if (s.size() == 0)
    //             s += (s_temp + ' ');
    //             // else
    //             //     s += s_temp;
    //         }
    //     }
    //     // if (s.size() != 0)
    //     //     s.pop_back();
    //     if (s.size() == 0)
    //     {
    //         start=0;
    //         string s_temp(str.begin() + start, str.end());
    //         s_temp = Reverse(s_temp);
    //         // if(s.size()==0)
    //         s += s_temp;
    //     }
    //     else
    //     {
    //         string s_temp(str.begin() + start + 1, str.end());
    //         s_temp = Reverse(s_temp);
    //         // if(s.size()==0)
    //         s += s_temp;
    //     }
    //     // else
    //     //     s += s_temp;
    //     return s;
    // }
    void ReverseSentence_repeat(string &str, int start, int end)
    {
        while(start<end)
        {
            swap(str[start],str[end]);
            start++;
            end--;
        }
    }
    string ReverseSentence(string str)
    {
        if(str.size()==0)
            return str;
        
        ReverseSentence_repeat(str,0,str.size()-1);

        int left=0;
        int right=0;
        for(int i=0;i<str.size();i++)
        {
            if(str[i]==' ')
            {
                right=i-1;
                ReverseSentence_repeat(str,left,right);
                left=i+1;
            }                
        }
        ReverseSentence_repeat(str,left,str.size()-1);
        return str;
    }
};

int main()
{
    string str = "I am a student.";
    // string str = "student.";
    Solution solution;
    string str2 = solution.ReverseSentence(str);
    return 0;
}