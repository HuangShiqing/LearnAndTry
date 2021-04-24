#include <iostream>
#include <vector>
using namespace std;

// numSquares(n)=min(numSquares(n-k) + 1)  ∀k∈square numbers

class Solution {
public:
    int numSquares(int n) {
        vector<int> nums;
        vector<int> r;
        int i = 1;
        while (1) {
            if (i * i < n) {
                nums.push_back(i * i);
                i++;
            } else
                break;
        }

        vector<int> dp(n + 1);
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            int minNum = INT32_MAX;
            int j = 0;
            while (i - nums[j] >= 0) {
                if (dp[i - nums[j]] + 1 < minNum)
                    minNum = dp[i - nums[j]] + 1;
                j++;
            }
            dp[i] = minNum;
        }
        return dp[n];
    }
};