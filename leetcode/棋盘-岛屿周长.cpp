// 463. 岛屿的周长
// 给定一个 row x col 的二维网格地图 grid ，其中：grid[i][j] = 1 表示陆地， grid[i][j] = 0 表示水域。
// 网格中的格子 水平和垂直 方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，一个或多个表示陆地的格子相连组成的岛屿）。
// 岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。格子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100 。计算这个岛屿的周长。

// 示例 1：
// 输入：grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
// 输出：16
// 解释：它的周长是上面图片中的 16 个黄色的边

// 示例 2：
// 输入：grid = [[1]]
// 输出：4

// 示例 3：
// 输入：grid = [[1,0]]
// 输出：4

// 2021年06月20日11:05:36
// 准备第一次社招
// 思路: 经典的岛屿题. 我们遍历所有点, 先后从一个未上过的点上岛, 上岛后先将flag蔓延到岛上的其他点, 
// 这样就不会重复上岛. 执行这个过程中需要记录什么则根据题目要求来. 这里周长就是周围4个岛是水的数量, 因此
// 加个返回值表示是水还是陆地

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid, int i, int j, int& length){
        if(i>grid.size()-1||i<0||j>grid[0].size()-1||j<0)
            return 1;
        
        if(grid[i][j]==0)
            return 1;
        if(grid[i][j]==2)
            return 0;
        
        grid[i][j] = 2;

        int r1 = islandPerimeter(grid, i-1, j, length);
        int r2 = islandPerimeter(grid, i, j-1, length);
        int r3 = islandPerimeter(grid, i+1, j, length);
        int r4 = islandPerimeter(grid, i, j+1, length);

        length+=(r1+r2+r3+r4);
        return 0;
    }

    int islandPerimeter(vector<vector<int>>& grid) {
        int length = 0;
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                islandPerimeter(grid, i, j, length);
            }
        }
        return length;
    }
};