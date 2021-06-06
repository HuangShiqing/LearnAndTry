// 剑指 Offer 64. 求1+2+…+n
// 求 1+2+...+n ，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。

// 示例 1：
// 输入: n = 3
// 输出: 6

// 示例 2：
// 输入: n = 9
// 输出: 45

// -------------------第三次刷-----------------------
// 2021年6月4日10:31:16
// 准备第一次社招
// 思路: 递归, 然后用逻辑运算符的短路性质作为停止条件. 

class Solution {
public:
    int sumNums(int n) {
        n&&(n+=sumNums(n-1));
        return n;
    }
};


class Temp
{
public:
    Temp()
    {
        ++N;
        Sum += N;
    }

    static void Reset()
    {
        N = 0;
        Sum = 0;
    }
    static unsigned int GetSum() { return Sum; }

private:
    static unsigned int N;
    static unsigned int Sum;

};

unsigned int Temp::N=0;
unsigned int Temp::Sum=0;



class Solution
{
public:
    int Sum_Solution(int n)
    {
        Temp::Reset();
        Temp *a = new Temp[n];
        delete []a;
        a=nullptr;
        return Temp::GetSum();
    }
};

int main()
{
    int n = 3;
    Solution solution;
    int result = solution.Sum_Solution(n);
    return 0;
}