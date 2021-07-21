// 695. 岛屿的最大面积
// 给定一个包含了一些 0 和 1 的非空二维数组 grid 。
// 一个 岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在水平或者竖直方向上相邻。你可以假设 grid 的四个边缘都被 0（代表水）包围着。
// 找到给定的二维数组中最大的岛屿面积。(如果没有岛屿，则返回面积为 0 。)

// 示例 1:
// [[0,0,1,0,0,0,0,1,0,0,0,0,0],
//  [0,0,0,0,0,0,0,1,1,1,0,0,0],
//  [0,1,1,0,1,0,0,0,0,0,0,0,0],
//  [0,1,0,0,1,1,0,0,1,0,1,0,0],
//  [0,1,0,0,1,1,0,0,1,1,1,0,0],
//  [0,0,0,0,0,0,0,0,0,0,1,0,0],
//  [0,0,0,0,0,0,0,1,1,1,0,0,0],
//  [0,0,0,0,0,0,0,1,1,0,0,0,0]]
// 对于上面这个给定矩阵应返回 6。注意答案不应该是 11 ，因为岛屿只能包含水平或垂直的四个方向的 1 。

// 示例 2:
// [[0,0,0,0,0,0,0,0]]
// 对于上面这个给定的矩阵, 返回 0。

// 2021年06月20日11:05:36
// 准备第一次社招
// 思路: 经典的岛屿题. 我们遍历所有点, 先后从一个未上过的点上岛, 上岛后先将flag蔓延到岛上的其他点, 
// 这样就不会重复上岛. 执行这个过程中需要记录什么则根据题目要求来

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void maxAreaOfIsland(vector<vector<int>>& grid, int i, int j, int& area){
        if(i>grid.size()-1||i<0||j>grid[0].size()-1||j<0)
            return;
        
        if(grid[i][j]!=1)
            return;
        
        area++;
        grid[i][j] = 2;

        maxAreaOfIsland(grid, i-1, j, area);
        maxAreaOfIsland(grid, i, j-1, area);
        maxAreaOfIsland(grid, i+1, j, area);
        maxAreaOfIsland(grid, i, j+1, area);
    }

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int max_area = INT32_MIN;
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                int area = 0;
                maxAreaOfIsland(grid, i, j, area);
                max_area = max(max_area, area);
            }
        }
        return max_area;
    }
};