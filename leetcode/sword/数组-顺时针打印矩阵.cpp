// 剑指 Offer 29. 顺时针打印矩阵
// 输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

// 示例 1：
// 输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
// 输出：[1,2,3,6,9,8,7,4,5]

// 示例 2：
// 输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
// 输出：[1,2,3,4,8,12,11,10,9,5,6,7]

// 限制：
// 0 <= matrix.length <= 100
// 0 <= matrix[i].length <= 100

// -------------------第三次刷-----------------------
// 2021年5月13日10:38:49
// 准备第一次社招
// 思路: 递归, 外面一圈, 完了里面一圈. 每一圈
#include <vector>
using namespace std;

class Solution {
public:
    //i是竖的, j是横的
    void spiralOrder_repeat(vector<vector<int>>& matrix, vector<int>& v, int i_start, int i_end, int j_start, int j_end) {

        if(i_start>i_end&&j_start>j_end)
            return;

        if(i_start==i_end&&j_start==j_end)//只构成一个点
            v.push_back(matrix[i_start][j_start]);
        else if(i_start==i_end){//只构成一个横线, 每条线全部都打
            for(int j=j_start;j<=j_end;j++)
                v.push_back(matrix[i_start][j]);            
        }
        else if(j_start==j_end){//只构成一个竖线, 每条线全部都打
            for(int i=i_start;i<=i_end;i++)
                v.push_back(matrix[i][j_start]);
        }
        else{//构成一个圈, 每条线末尾一位不打, 留给下一条线
            for(int j=j_start;j<j_end;j++)
                v.push_back(matrix[i_start][j]);
            for(int i=i_start;i<i_end;i++)
                v.push_back(matrix[i][j_end]);
            for(int j=j_end;j>j_start;j--)
                v.push_back(matrix[i_end][j]);
            for(int i=i_end;i>i_start;i--)
                v.push_back(matrix[i][j_start]);
        }

        spiralOrder_repeat(matrix, v, i_start+1, i_end-1, j_start+1, j_end-1);

    }

    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> v;
        if (matrix.size() == 0)
            return v;

        spiralOrder_repeat(matrix, v, 0, matrix.size()-1, 0, matrix[0].size()-1);
        return v;
    }
};