// 剑指 Offer 47. 礼物的最大价值
// 在一个 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于 0）。你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格、
// 直到到达棋盘的右下角。给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？

// 示例 1:

// 输入: 
// [
//   [1,3,1],
//   [1,5,1],
//   [4,2,1]
// ]
// 输出: 12
// 解释: 路径 1→3→5→2→1 可以拿到最多价值的礼物

// -------------------第三次刷-----------------------
// 2021年5月28日19:43:49
// 准备第一次社招
// 思路: 递归回溯大矩阵会超时
// 思路2: 动态规划. dp[i][j]代表当前位置为终点时总共的最大礼物价值. dp[i][j] = max(dp[i-1][j], dp[i][j-1])+grid[i][j], 即当前格价值加上上或者左格的dp

#include <vector>
using namespace std;

//递归会超时
// class Solution {
// public:
//     int biggest_value=0;
//     void maxValue(vector<vector<int>>& grid, int h, int w, int& value){
//         if(h>=grid.size() || w>=grid[0].size()){
//             return ;
//         }

//         value += grid[h][w];
//         if(h==grid.size()-1 && w==grid[0].size()-1){
//             if(value>biggest_value)
//                 biggest_value = value;
//         }
//         else{
//             maxValue(grid, h+1, w, value);
//             maxValue(grid, h, w+1, value);
//         }        
//         value -= grid[h][w];

//         return;
//     }

//     int maxValue(vector<vector<int>>& grid) {   
//         int value=0;
//         maxValue(grid, 0, 0, value);
//         return biggest_value;
//     }
// };


class Solution {
public:
    int maxValue(vector<vector<int>>& grid){
        int h=grid.size();
        int w=grid[0].size();
        vector<vector<int>> dp(h, vector<int>(w, 0));
        
        //先赋值0,0点
        dp[0][0] = grid[0][0];
        //赋值第一行和第一列
        for(int i=1;i<w;i++)
            dp[0][i] = dp[0][i-1]+grid[0][i];
        for(int j=1;j<h;j++)
            dp[j][0] = dp[j-1][0]+grid[j][0];
        //按公式赋值剩下的
        for(int i=1;i<h;i++)
            for(int j=1;j<w;j++)
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])+grid[i][j];
        
        return dp[h-1][w-1];
    }
};

int main(){
    vector<vector<int>> v{{1,3,1},{1,5,1},{4,2,1}};
    Solution s;
    int r = s.maxValue(v);
    return r;
}