// 剑指 Offer 46. 把数字翻译成字符串
// 给定一个数字，我们按照如下规则把它翻译为字符串：0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25 翻译成 “z”。一个数字可能有多个翻译。请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。

// 示例 1:
// 输入: 12258
// 输出: 5
// 解释: 12258有5种不同的翻译，分别是"bccfi", "bwfi", "bczi", "mcfi"和"mzi"

// -------------------第三次刷-----------------------
// 2021年5月28日14:36:41
// 准备第一次社招
// 思路: 递归. count++的条件是index刚好指向[...12]3. 


#include <string>
using namespace std;
class Solution {
public:
    void translateNum(string s, int index, int& count){     
        if(index==s.size()){
            count++;
            return;
        }            
        if(index>s.size())
            return;   
        
        translateNum(s, index+1, count);
        if(string(s, index, 2)<=string("25") && index<=s.size()-2 && s[index] != '0')//这里要手动确保不能出现'05'这样的数
            translateNum(s, index+2, count);
        
        return;
    }

    int translateNum(int num) {
        int count = 0;
        string s = to_string(num);

        translateNum(s, 0, count);

        return count;
    }
};

int main(){
    Solution s;
    
    return s.translateNum(506);
}