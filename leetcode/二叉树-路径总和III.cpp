#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// 437. 路径总和 III
// 给定一个二叉树，它的每个结点都存放着一个整数值。
// 找出路径和等于给定数值的路径总数。
// 路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
// 二叉树不超过1000个节点，且节点数值范围是 [-1000000,1000000] 的整数。

// 示例：
// root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8
//       10
//      /  \
//     5   -3
//    / \    \
//   3   2   11
//  / \   \
// 3  -2   1
// 返回 3。和等于 8 的路径有:
// 1.  5 -> 3
// 2.  5 -> 2 -> 1
// 3.  -3 -> 11

// -------------------第二次刷-----------------------
// 2021年7月15日10:20:46
// 准备第一次社招
// 思路: 首先不要考虑从非根节点出发. 那么就比较简单的dfs即可. 然后题目说可以从非根节点出发, 
// 那么就第二重递归pathSum从不同的node出发进行dfs
// 挺好的题解https://leetcode-cn.com/problems/path-sum-iii/solution/yi-pian-wen-zhang-jie-jue-suo-you-er-cha-smch/

class Solution {
public:
    int count = 0;
    int pathSum(TreeNode *root, int targetSum) {
        if (!root)
            return 0;
        dfs(root, targetSum);            //第一重递归, 以root为起始点查找路径
        pathSum(root->left, targetSum);  //第二重递归, 左子树递归
        pathSum(root->right, targetSum);  //第二重递归, 右子树递归
        return count;
    }

    void dfs(TreeNode *root, int sum)
    {
        if (!root)
            return;
        sum -= root->val;
        if (sum == 0) //注意不要return,因为不要求到叶节点结束,所以一条路径下面还可能有另一条
            count++;  //如果找到了一个路径全局变量就+1
        dfs(root->left, sum);
        dfs(root->right, sum);
    }    
};