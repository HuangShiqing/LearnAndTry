// page 51
#include <iostream>

// void replaceSpace(char *str, int length)
// {
//     if (str == nullptr || length <= 0)
//         return;

//     int i = 0;
//     int num_blank = 0;
//     int length_original = 0;
//     while (str[i] != '\0')
//     {
//         if (str[i] == ' ')
//             num_blank++;
//         i++;
//         length_original++;
//     }

//     int length_new = length_original + 2 * num_blank;
//     if (length_new > length)
//         return;

//     int index_original= length_original;
//     int index_new = length_new;
//     while(index_original >= 0)
//     {
//         if(str[index_original]==' ')
//         {
//             str[index_new--] = '0';
//             str[index_new--] = '2';
//             str[index_new--] = '%';
//         }
//         else
//         {
//             str[index_new--] = str[index_original];
//         }
//         index_original--;

//     }
// }

class Solution {
public:
    void replaceSpace(char* str, int length) {
        if (str == nullptr || length < 0)
            return;

        int num_blank = 0;
        int num_original = 0;
        char* p1 = str;
        while (*p1 != '\0') {
            if (*p1 == ' ')
                num_blank++;
            num_original++;
            p1++;
        }
        num_original++;
        if (num_original + 2 * num_blank > length)
            return;

        char* p2 = p1 + 2 * num_blank;
        //结束条件是两者相遇
        while (p1 != p2) {
            if (*p1 == ' ') {
                *p2 = '0';
                p2--;
                *p2 = '2';
                p2--;
                *p2 = '%';
            } else {
                *p2 = *p1;
            }
            p1--;
            p2--;
        }
    }
};

int main() {
    char str[] = "Hello World";

    Solution solution;
    solution.replaceSpace(str, 50);
    return 0;
}

// 剑指 Offer 05. 替换空格
// 请实现一个函数，把字符串 s 中的每个空格替换成"%20"。
// 示例 1：
// 输入：s = "We are happy."
// 输出："We%20are%20happy."

// 2021年04月24日15:22:50
// 准备第一次社招

// 思路:
// 如果是从左往右遍历, 每次找到空格然后插入"%20"则每次都需要移动后面的字符串, 效率太低
// 可以先统计总共有几个空格, 一次性resize字符串的大小
// 然后双指针i, j从右往左遍历, 原指针i遇到空格则新指针j倒序赋值"%20", 遇到非空格则s[j] = s[i]
// 当i==j时代表左边没有空格了退出循环
#include <string>
using namespace std;

class Solution2 {
public:
    string replaceSpace(string s) {
        int blank_count = 0;
        for (char c : s) {
            if (c == ' ')
                blank_count++;
        }
        int old_size = s.size();
        int new_size = old_size + 2 * blank_count;
        s.resize(new_size);

        int i = old_size - 1;
        int j = new_size - 1;
        while (i != j) {
            if (s[i] == ' ') {
                s[j] = '0';
                j--;
                s[j] = '2';
                j--;
                s[j] = '%';
            } else {
                s[j] = s[i];
            }
            j--;
            i--;
        }
        return s;
    }
};