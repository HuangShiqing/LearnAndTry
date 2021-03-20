// 如果在扫描到数组中的第i个数字时，只要我们能够记住之前的i-1个数字中的最小值，
// 就能算出在当前价位卖出时可能得到的最大利润。
#include <vector>
using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int minBefore = prices[0];
        int maxResult = INT32_MIN;
        for(int i = 1; i< prices.size(); i++)
        {
            int tempMaxResult = prices[i] - minBefore;
            if(tempMaxResult > maxResult)
                maxResult = tempMaxResult;

            if(prices[i]<minBefore)
                minBefore = prices[i];
        }
        // 如果你不能获取任何利润，返回 0
        if(maxResult < 0)
            return 0;
        else
            return maxResult;
    }
};