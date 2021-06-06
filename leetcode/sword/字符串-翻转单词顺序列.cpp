// 剑指 Offer 58 - I. 翻转单词顺序
// 输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。为简单起见，标点符号和普通字母一样处理。例如输入字符串"I am a student. "，则输出"student. a am I"。

// 示例 1：
// 输入: "the sky is blue"
// 输出: "blue is sky the"

// 示例 2：
// 输入: "  hello world!  "
// 输出: "world! hello"
// 解释: 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。

// 示例 3：
// 输入: "a good   example"
// 输出: "example good a"
// 解释: 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。

// 说明：
// 无空格字符构成一个单词。
// 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
// 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。

// -------------------第三次刷-----------------------
// 2021年6月3日10:30:16
// 准备第一次社招
// 思路: 双尾指针. right找单词尾(第一个非空格), left找单次头(第一个空格), 然后left+1为start, right-(left+1)+1为len得到substr,后面加一个空格即可
// 得到一个单词后, right=left

class Solution {
public:
    string reverseWords(string s) {
        string res;
        int n = s.size();
        if(n == 0) 
            return res;
        int right = n - 1;
        while(right >= 0){
            //从后往前寻找第一字符
            while(right >= 0 && s[right] == ' ') 
                right--;
            if(right < 0) 
                break;

            //从后往前寻找第一个空格
            int left = right;
            while( left >= 0 && s[left] != ' ' ) 
                left--;

            //添加单词到结果
            res += s.substr(left + 1, right - left);
            res += ' ';

            //继续往前分割单词
            right = left;
        }
        //去除最后一个字符空格
        if (!res.empty()) 
            res.pop_back();
        return res;
    }
};

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