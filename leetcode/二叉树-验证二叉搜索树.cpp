#include <iostream>
#include <vector>
using namespace std;

// 二叉搜索树定义:
// 1.若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
// 2.若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
// 3.它的左右子树也为二叉搜索树
// 4.二叉搜索树「中序遍历」得到的值构成的序列一定是升序的

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    long pre =LONG_MIN;//避免最左边的也是INT_MIN
    bool isValidBST(TreeNode* root) {
        if (root == nullptr)
            return true;

        //访问左子树
        if (!isValidBST(root->left))
            return false;
        //访问当前节点
        if (root->val <= pre)
            return false;
        pre = root->val;
        // 访问右子树
        return isValidBST(root->right);
    }
};