#include <iostream>
#include <vector>
using namespace std;

// 543. 二叉树的直径
// 给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。
// 这条路径可能穿过也可能不穿过根结点。
// 示例 :
// 给定二叉树
//           1
//          / \
//         2   3
//        / \     
//       4   5    
// 返回 3, 它的长度是路径 [4,2,1,3] 或者 [5,2,1,3]。
// 注意：两结点之间的路径长度是以它们之间边的数目表示。

// -------------------第二次刷-----------------------
// 2021年7月19日14:35:50
// 准备第一次社招
// 思路: 求直径(任意两个节点路径长度的最大值), 那么就遍历所有的node, 找到其left node和right node深度后累加即为该node
// 相关的最大直径. 那么其实就是合并了两道题, 一题是求每个node的深度, 另外一题是遍历node找最大值

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
    int maxd = 0;

public:
    int diameterOfBinaryTree(TreeNode* root) {
        depth(root);
        return maxd;
    }
    int depth(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        int Left = depth(node->left);
        int Right = depth(node->right);
        maxd = max(Left + Right, maxd);  //将每个节点最大直径(左子树深度+右子树深度)当前最大值比较并取大者
        return max(Left, Right) + 1;  //返回节点深度
    }
};