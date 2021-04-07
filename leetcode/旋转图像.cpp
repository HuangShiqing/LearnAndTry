// 对于矩阵中第 i 行的第 j个元素，在旋转后，它出现在倒数第 i 列的第 j 个位置,即matrix[i][j] = matrix[n - 1 - j][i]
#include <algorithm>
#include <vector>
using namespace std;

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