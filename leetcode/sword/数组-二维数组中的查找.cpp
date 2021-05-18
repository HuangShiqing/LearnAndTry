#include <iostream>
#include <vector>
using namespace std;

bool Find(int target, vector<vector<int>> array) {
    // 数组表示,array.size()=4,array[0].size()=3
    //   1   2    8    9
    // [[4],[7],[10],[13]]
    //   6   8   11   15

    // 这个是colums，竖着的列数
    if (array.size() == 0)
        return false;
    // 这个是rows，横着的行数
    if (array[0].size() == 0)
        return false;

    int rows = 0;
    int columns = array.size() - 1;

    while (true) {
        // 小于右上角，边界往左
        if (target < array[columns][rows]) {
            if (columns > 0)
                columns--;
            else
                return false;
        }
        // 大于右上角，边界往下
        else if (target > array[columns][rows]) {
            if (rows < array[0].size() - 1)
                rows++;
            else
                return false;
        } else {
            return true;
        }
    }
}

// 剑指 Offer 04. 二维数组中的查找
// 在一个 n * m
// 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
// 示例:
// 现有矩阵 matrix 如下：
// [
//   [1,   4,  7, 11, 15],
//   [2,   5,  8, 12, 19],
//   [3,   6,  9, 16, 22],
//   [10, 13, 14, 17, 24],
//   [18, 21, 23, 26, 30]
// ]
// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 2021年04月24日15:22:50
// 准备第一次社招
// 思路: 核心就是右上角的数. 建立交点位于右上角的横竖两根线, target>交点则横线下移, target<交点则竖线左移,
// target==交点则找到, 横竖线越界则找不到
class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0)
            return false;

        int h_max = matrix.size();
        int w_max = matrix[0].size();

        int h = 0;
        int w = w_max - 1;
        while (h < h_max && w >= 0) {
            if (target > matrix[h][w])
                h++;
            else if (target < matrix[h][w])
                w--;
            else
                return true;
        }
        return false;
    }
};