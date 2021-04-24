#include <iostream>
#include <vector>
using namespace std;

// 动态规划
// 设置dp[i]代表i的二进制位数
// dp[i]等于dp[i右移一位]加上i的最低位是否有1
// dp[i] = dp[i>>1]+i&1
// dp[0] = 0;

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> bits(num + 1);
        for (int i = 1; i <= num; i++) {
            bits[i] = bits[i >> 1] + (i & 1);
        }
        return bits;
    }
};