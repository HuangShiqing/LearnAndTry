// 剑指 Offer 62. 圆圈中最后剩下的数字
// 0,1,···,n-1这n个数字排成一个圆圈，从数字0开始，每次从这个圆圈里删除第m个数字（删除后从下一个数字开始计数）。求出这个圆圈里剩下的最后一个数字。

// 例如，0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。

// 示例 1：
// 输入: n = 5, m = 3
// 输出: 3

// 示例 2：
// 输入: n = 10, m = 17
// 输出: 2

// -------------------第三次刷-----------------------
// 2021年6月3日15:56:28
// 准备第一次社招
// 思路: 首先对于一个数组0,1,2,3,4, start索引假设为3, 那么删除其后的第4个数后指向的数的index为3, 可以表示为 (3+4)%5

class Solution {
public:
    int f(int n, int m){
        if(n==1)
            return 0;
        
        int x = f(n-1, m);

        return (m+x)%n;
    }

    int lastRemaining(int n, int m) {
        return f(n, m);
    }
};

//page 300
#include <list>
#include <vector>
using namespace std;

class Solution
{
public:
    // int LastRemaining_Solution(int n, int m)
    // {
    //     if (n < 1 || m < 1)
    //         return -1;
    //     list<int> numbers;
    //     for (int i = 0; i < n; i++)
    //         numbers.push_back(i);

    //     list<int>::iterator current = numbers.begin();
    //     while (numbers.size() > 1)
    //     {

    //         for (int i = 1; i < m; i++)
    //         {
    //             current++;
    //             if (current == numbers.end())
    //                 current = numbers.begin();
    //         }
    //         list<int>::iterator next = ++current;
    //         if (next == numbers.end())
    //             next = numbers.begin();
    //         current--;
    //         numbers.erase(current);
    //         current = next;
    //     }
    //     return *current;
    // }
    int LastRemaining_Solution(int n, int m)
    {
        if (n < 1 || m < 1)
            return -1;
        vector<int> v;
        for (int i = 0; i < n; i++)
            v.push_back(i);

        int index_start = 0;
        int erase = index_start + m - 1;
        while (v.size() > 1)
        {
            //注意这里要用while
            while(erase >= v.size())
                erase -= v.size();
            v.erase(v.begin() + erase);
            index_start = erase;
            erase = index_start + m - 1;
        }
        return v[0];
    }
};

int main()
{
    int n = 0;
    int m = 0;
    Solution solution;
    solution.LastRemaining_Solution(n, m);
    return 0;
}