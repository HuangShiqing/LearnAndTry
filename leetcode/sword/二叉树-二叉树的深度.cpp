// 剑指 Offer 55 - I. 二叉树的深度
// 输入一棵二叉树的根节点，求该树的深度。从根节点到叶节点依次经过的节点（含根、叶节点）形成树的一条路径，最长路径的长度为树的深度。

// 例如：

// 给定二叉树 [3,9,20,null,null,15,7]，

//     3
//    / \
//   9  20
//     /  \
//    15   7
// 返回它的最大深度 3 。

// -------------------第三次刷-----------------------
// 2021年6月1日10:04:34
// 准备第一次社招
// 思路1: 从上往下数, 很简单, 递归遍历即可. 
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    int g_depth=0;
    void maxDepth(TreeNode* root, int depth) {
        if(root==nullptr)
            return;
        
        depth++;
        if(depth>g_depth)
            g_depth = depth;

        maxDepth(root->left, depth);
        maxDepth(root->right, depth);
        depth--;        
    }

    int maxDepth(TreeNode* root) {
        maxDepth(root, 0);
        return g_depth;
    }
};

//思路2: 从下往上数. 返回值是pRoot的深度
int TreeDepth(TreeNode *pRoot)
{
    //递归停止条件
    if (pRoot == nullptr)
        return 0;
    //父层是子层的深度加1
    int left = TreeDepth(pRoot->left);
    int right = TreeDepth(pRoot->right);
    return (left > right) ? (left + 1) : (right + 1);
}

//page 271
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    // TreeNode(int x) :
    // 		val(x), left(NULL), right(NULL) {
    // }
};

class Solution
{
public:
    // int TreeDepth(TreeNode* pRoot)
    // {
    //     if(pRoot==nullptr)
    //         return 0;
    //     int left = TreeDepth(pRoot->left);
    //     int right = TreeDepth(pRoot->right);
    //     return (left>right)?(left+1):(right+1);
    // }

    // int depth=0;
    // int max_depth=0;
    // void TreeDepth_repeat(TreeNode* pRoot)
    // {
    //     //进来深度加1
    //     depth++;
    //     if(depth>max_depth)
    //         max_depth=depth;

    //     if(pRoot->left)
    //         TreeDepth_repeat(pRoot->left);
    //     if(pRoot->right)
    //         TreeDepth_repeat(pRoot->right);
    //     //准备退出了深度减一
    //     depth--;
    // }
    // int TreeDepth(TreeNode* pRoot)
    // {
    //     if(pRoot==nullptr)
    //         return 0;
    //     TreeDepth_repeat(pRoot);
    //     return max_depth;
    // }

    int TreeDepth(TreeNode *pRoot)
    {
        //递归停止条件
        if (pRoot == nullptr)
            return 0;
        //父层是子层的深度加1
        int left = TreeDepth(pRoot->left);
        int right = TreeDepth(pRoot->right);
        return (left > right) ? (left + 1) : (right + 1);
    }
};