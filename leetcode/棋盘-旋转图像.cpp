#include <algorithm>
#include <vector>
using namespace std;

// 48. 旋转图像
// 给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。
// 你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。

// 示例 1：
// 输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
// 输出：[[7,4,1],[8,5,2],[9,6,3]]

// 示例 2：
// 输入：matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
// 输出：[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

// 示例 3：
// 输入：matrix = [[1]]
// 输出：[[1]]

// 示例 4：
// 输入：matrix = [[1,2],[3,4]]
// 输出：[[3,1],[4,2]]

// -------------------第二次刷-----------------------
// 2021年6月10日10:30:53
// 准备第一次社招
// 思路:
// 找到旋转的规律, old矩阵中第 i 行的第 j列的数matrix[i][j], 经过旋转后, 出现在new矩阵中的第j行倒数第 i 列, 即matrix[j][n-1-i]. 
// 换一下顺序, 即new矩阵中的数matrix[i][j]来自于old矩阵中的matrix[n-1-j][i].
// 每次处理一个数, 位置点A=点B的数, 因为点B的数移动到了位置点A了, 那么要考虑位置点B的数来自于哪里. 那就继续套公式, 位置点B=点C的数, 
// 位置点C=点D的数, 位置点D=点A的数, 4次之后刚好绕一圈
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        //整个矩阵分四块,图示见https://leetcode-cn.com/problems/rotate-image/solution/xuan-zhuan-tu-xiang-by-leetcode-solution-vu3m/
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < (n + 1) / 2; ++j) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[n - 1 - j][i];
                matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];  //套上面的公式
                matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
                matrix[j][n - i - 1] = temp;
            }
        }
    }
};