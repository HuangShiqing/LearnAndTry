#include <iostream>
#include <vector>

using namespace std;

// [非常好的棋盘遍历正规教程](https://leetcode-cn.com/problems/number-of-islands/solution/dao-yu-lei-wen-ti-de-tong-yong-jie-fa-dfs-bian-li-/)

// 200. 岛屿数量
// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
// 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
// 此外，你可以假设该网格的四条边均被水包围。

// 示例 1：
// 输入：grid = [
//   ["1","1","1","1","0"],
//   ["1","1","0","1","0"],
//   ["1","1","0","0","0"],
//   ["0","0","0","0","0"]
// ]
// 输出：1

// 示例 2：
// 输入：grid = [
//   ["1","1","0","0","0"],
//   ["1","1","0","0","0"],
//   ["0","0","1","0","0"],
//   ["0","0","0","1","1"]
// ]
// 输出：3

// 2021年06月20日11:05:36
// 准备第一次社招
// 思路: 经典的岛屿题. 我们遍历所有点, 先后从一个未上过的点上岛, 上岛后先将flag蔓延到岛上的其他点, 
// 这样就不会重复上岛. 执行这个过程中需要记录什么则根据题目要求来

class Solution {
public:
    int count = 0;
    int numIslands(vector<vector<char>>& grid) {
        //起始点可以为任一一个棋格
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size(); j++) {
                if(grid[i][j] == '1') {
                    count++;
                    dfs(grid, i, j);
                }
            }
        }

        return count;
    }
    
    void dfs(vector<vector<char>>& grid, int r, int c) {
        //判断 base case
        //如果坐标（r,c）超出了网格范围，直接返回
        if(!isArea(grid, r, c)) 
            return;
        
        //如果这个格子不是岛屿，直接返回
        if (grid[r][c] != '1') 
            return;
        
        grid[r][c] = 2; //将格子标记为【已遍历过】
        
        //访问上、下、左、右四个相邻结点
        dfs(grid, r-1, c);
        dfs(grid, r+1, c); 
        dfs(grid, r, c-1); 
        dfs(grid, r, c+1);
    }

    //判断坐标（r,c）是否在网格中
    bool isArea(vector<vector<char>>& grid, int r, int c) {
        return (0 <= r && r < grid.size() && 0 <= c && c < grid[0].size());
    }

};