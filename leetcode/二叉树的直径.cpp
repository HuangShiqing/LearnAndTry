#include <iostream>
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