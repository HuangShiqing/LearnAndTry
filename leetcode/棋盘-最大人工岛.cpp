// 827. 最大人工岛
// 给你一个大小为 n x n 二进制矩阵 grid 。最多 只能将一格 0 变成 1 。
// 返回执行此操作后，grid 中最大的岛屿面积是多少？
// 岛屿 由一组上、下、左、右四个方向相连的 1 形成。

// 示例 1:
// 输入: grid = [[1, 0], [0, 1]]
// 输出: 3
// 解释: 将一格0变成1，最终连通两个小岛得到面积为 3 的岛屿。

// 示例 2:
// 输入: grid = [[1, 1], [1, 0]]
// 输出: 4
// 解释: 将一格0变成1，岛屿的面积扩大为 4。

// 示例 3:
// 输入: grid = [[1, 1], [1, 1]]
// 输出: 4
// 解释: 没有0可以让我们变成1，面积依然为 4。

// 2021年06月20日14:09:43
// 准备第一次社招
// 思路: 第一步先求出各个点所在的岛屿的面积, 第二步然后找到一个连接点使多个岛屿连接成最大的岛.
// 第一步就是题目"岛屿的最大面积", 然后要把岛屿的每个点都标上该岛屿的面积(但是这样做会有个问题, 看第二步)
// 第二步, 找连接点, 遍历即可, 某的点上下左右之和即为最大人工岛. 但是有可能上和左是一个岛屿. 因此把第一步
// 记录每个岛的面积不直接用二维数组, 而是在二维数组里放索引, 真正的面积放在另外一个一维数组里
// 注意: 索引从2开始, 以防止海洋的0和陆地的1和索引冲突
// 注意: 可能第二步里根本没有海洋, 就要返回最大
// 思路比较简单, 但是实现貌似不太优雅
// 执行用时：1488 ms, 在所有 C++ 提交中击败了5.09%的用户
// 内存消耗：308.1 MB, 在所有 C++ 提交中击败了5.78%的用户

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid, vector<vector<bool>>& flag, int i, int j, int& area, vector<int>& areas, int index){
        if(i>grid.size()-1||i<0||j>grid[0].size()-1||j<0)
            return -1;
        if(flag[i][j]==false)
            return -1;

        if(grid[i][j]==0){
            flag[i][j]=false;
            return -1;
        }
            
        
        area++;
        flag[i][j]=false;

        int r1 = largestIsland(grid, flag, i+1, j, area, areas, index);
        int r2 = largestIsland(grid, flag, i, j+1, area, areas, index);
        int r3 = largestIsland(grid, flag, i-1, j, area, areas, index);
        int r4 = largestIsland(grid, flag, i, j-1, area, areas, index);
        
        int max_area = max(max(max(max(r1, area), r2), r3), r4);
        grid[i][j] = index;
        areas[index] = max(areas[index], max_area);
        return max_area;
    }

    int largestIsland(vector<vector<int>>& grid) {
        vector<vector<bool>> flag(grid.size(), vector<bool>(grid[0].size(), true));
        int index=2;
        vector<int> areas(grid.size()*grid[0].size()+2);
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(flag[i][j]==false)
                    continue;
                int area = 0;
                int max_area = largestIsland(grid, flag, i, j, area, areas, index);
                index++;
            }
        }

        int max_area = -1;
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(grid[i][j]==0){
                    int area_tmp = 1;

                    int area_up = 0;
                    int up_index = -1;
                    if(i-1>=0&&grid[i-1][j]!=0){                        
                        up_index = grid[i-1][j];
                        area_up = areas[up_index];
                    }

                    int area_down = 0;
                    int down_index = -1;
                    if(i+1<grid.size()&&grid[i+1][j]!=0){                        
                        down_index = grid[i+1][j];
                        area_down = areas[down_index];
                    }

                    int area_left = 0;
                    int left_index = -1;
                    if(j-1>=0&&grid[i][j-1]!=0){                        
                        left_index = grid[i][j-1];
                        area_left = areas[left_index];
                    }

                    int area_right = 0;
                    int right_index = -1;
                    if(j+1<grid[0].size()&&grid[i][j+1]!=0){                        
                        right_index = grid[i][j+1];
                        area_right = areas[right_index];
                    }

                    unordered_map<int, int> map;
                    map[up_index] = area_up;
                    map[down_index] = area_down;
                    map[left_index] = area_left;
                    map[right_index] = area_right;

                    for (auto it = map.begin(); it != map.end(); it++) {
                        area_tmp+=it->second;
                    }

                    max_area = max(max_area, area_tmp);
                }
            }
        }
        if(max_area==-1)
            return areas[2];
        else
            return max_area;
    }
};


int main(){
    vector<vector<int>> vv= {{1,1},{1,0}};
    Solution s;
    int a = s.largestIsland(vv);
    return a;

}