// 剑指 Offer 27. 二叉树的镜像
// 请完成一个函数，输入一个二叉树，该函数输出它的镜像。

// 例如输入：
//      4
//    /   \
//   2     7
//  / \   / \
// 1   3 6   9
// 镜像输出：
//      4
//    /   \
//   7     2
//  / \   / \
// 9   6 3   1

// 示例 1：
// 输入：root = [4,2,7,1,3,6,9]
// 输出：[4,7,2,9,6,3,1]
 
// 限制：
// 0 <= 节点个数 <= 1000

// -------------------第三次刷-----------------------
// 2021年5月13日10:38:49
// 准备第一次社招
// 思路: 后序遍历. 根节点的操作即为swap
struct TreeNode {
    int val;
    struct TreeNode *left = nullptr;
    struct TreeNode *right = nullptr;
    TreeNode(int x) :
    		val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* mirrorTree_repeat(TreeNode* root) {
        if(root==nullptr)
            return nullptr;

        if(root->left)
            root->left = mirrorTree_repeat(root->left);
        if(root->right)
            root->right = mirrorTree_repeat(root->right);
        swap(root->left, root->right);
        
        return root;
    }

    TreeNode* mirrorTree(TreeNode* root) {
        if( root == nullptr)
            return nullptr;
        return mirrorTree_repeat(root);
    }
};

#include <iostream>
using namespace std;

struct TreeNode
{
    int val;
    struct TreeNode *left = nullptr;
    struct TreeNode *right = nullptr;
    // TreeNode(int x) :
    // 		val(x), left(NULL), right(NULL) {
    // }
};

// void Mirror(TreeNode *pRoot)
// {

//     if(pRoot==nullptr)
//         return ;
//     if(pRoot->left==nullptr&&pRoot->right==nullptr)
//         return ;

//     TreeNode *temp_l = pRoot->left;
//     TreeNode *pRoot_temp = pRoot;

//     pRoot_temp->left = pRoot_temp->right;
//     pRoot_temp->right = temp_l;

//     if(pRoot->left)
//         Mirror(pRoot_temp->left);
//     if(pRoot->right)
//         Mirror(pRoot_temp->right);

// }
void Mirror_repeat(TreeNode *pRoot)
{
    //需要递归的条件是非最底层的叶节点，即至少有一个子节点存在
    if (pRoot->left || pRoot->right)
    {
        if (pRoot->left)
            Mirror_repeat(pRoot->left);
        if (pRoot->right)
            Mirror_repeat(pRoot->right);
        swap(pRoot->left, pRoot->right);
    }
}
void Mirror(TreeNode *pRoot)
{    
    if(pRoot==nullptr)
        return;
    
    Mirror_repeat(pRoot);    
}

int main()
{
    // TreeNode tree_root = TreeNode(8);
    // TreeNode *ptree_root = &tree_root;
    // tree_root.left = TreeNode(6);
    TreeNode *ptree_root = new TreeNode;
    ptree_root->val = 8;
    ptree_root->left = new TreeNode;
    ptree_root->left->val = 6;
    ptree_root->right = new TreeNode;
    ptree_root->right->val = 10;
    ptree_root->left->left = new TreeNode;
    ptree_root->left->left->val = 5;
    ptree_root->left->right = new TreeNode;
    ptree_root->left->right->val = 7;
    ptree_root->right->left = new TreeNode;
    ptree_root->right->left->val = 9;
    ptree_root->right->right = new TreeNode;
    ptree_root->right->right->val = 11;

    if (ptree_root->right == nullptr)
        cout << "hi" << endl;
    Mirror(ptree_root);
}