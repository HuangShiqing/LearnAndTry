// 剑指 Offer 63. 股票的最大利润
// 假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖该股票一次可能获得的最大利润是多少？

// 示例 1:
// 输入: [7,1,5,3,6,4]
// 输出: 5
// 解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
//      注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。

// 示例 2:
// 输入: [7,6,4,3,1]
// 输出: 0
// 解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。

// -------------------第三次刷-----------------------
// 2021年6月3日10:30:16
// 准备第一次社招
// 思路:
// 如果在扫描到数组中的第i个数字时，只要我们能够记住之前的i-1个数字中的最小值，
// 就能算出在当前价位卖出时可能得到的最大利润。
#include <vector>
using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        if(!prices.size())
            return -1;

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