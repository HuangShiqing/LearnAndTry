#include <unordered_map>
using namespace std;

// 70. 爬楼梯
// 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
// 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
// 注意：给定 n 是一个正整数。

// 示例 1：
// 输入： 2
// 输出： 2
// 解释： 有两种方法可以爬到楼顶。
// 1.  1 阶 + 1 阶
// 2.  2 阶

// 示例 2：
// 输入： 3
// 输出： 3
// 解释： 有三种方法可以爬到楼顶。
// 1.  1 阶 + 1 阶 + 1 阶
// 2.  1 阶 + 2 阶
// 3.  2 阶 + 1 阶

// -------------------第二次刷-----------------------
// 2021年6月11日10:46:00
// 准备第一次社招
// 思路: 很简单, 没什么好说的

class Solution {
public:
    int climbStairs(int n) {
        if(n == 1)
            return 1;
        if(n == 2)
            return 2;

        vector<int> dp(n+1);
        dp[1] = 1;
        dp[2] = 2;

        for(int i=3;i<=n;i++){
            dp[i] = dp[i-1]+dp[i-2];
        }
        return dp[n];
    }
};

class Solution {
public:
    unordered_map<int, int> map;
    int climbStairs(int n) {
        if(n == 1)
            return 1;
        if(n == 2)
            return 2;
        
        
        if(map.count(n)==0)
        {
            int num = climbStairs(n-1)+climbStairs(n-2);
            map[n] = num;
            return num;
        }
        else
        {
            return map[n];
        }
        
        
    }
};