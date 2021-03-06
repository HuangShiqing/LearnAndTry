// 剑指 Offer 14- II. 剪绳子 II
// 给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m - 1] 。
// 请问 k[0]*k[1]*...*k[m - 1] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。

// 答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

// 示例 1：
// 输入: 2
// 输出: 1
// 解释: 2 = 1 + 1, 1 × 1 = 1

// 示例 2:
// 输入: 10
// 输出: 36
// 解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36

// -------------------第三次刷-----------------------
// 2021年5月11日14:52:37
// 准备第一次社招
// 思路1: 与剪绳子I没啥区别, 就是每次更新r的时候要取余
class Solution {
public:
    int cuttingRope(int n) {
        if(n==2)
            return 1;
        else if(n==3)
            return 2;
        else if(n==4)
            return 2*2;

        long long r = 1;
        while (n>=3) {
            r*=3;
            r%=(long)1e9+7;//更新后取余
            n-=3;
        }

        if(n==2){
            r*=2;
            r%=(long)1e9+7;//更新后取余
        }
        else if(n==1){
            r/=3;
            r = r*2*2;
            r%=(long)1e9+7;//更新后取余
        }
        else if(n==0){
            r%=(long)1e9+7;//更新后取余
        }
        return r;
        // return r%=(long)1e9+7;//更新后取余; 
    }
};