// 剑指 Offer 28. 对称的二叉树
// 请实现一个函数，用来判断一棵二叉树是不是对称的。如果一棵二叉树和它的镜像一样，那么它是对称的。

// 例如，二叉树 [1,2,2,3,4,4,3] 是对称的。
//     1
//    / \
//   2   2
//  / \ / \
// 3  4 4  3

// 但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:
//     1
//    / \
//   2   2
//    \   \
//    3    3

// 示例 1：
// 输入：root = [1,2,2,3,4,4,3]
// 输出：true

// 示例 2：
// 输入：root = [1,2,2,null,3,null,3]
// 输出：false

// 限制：
// 0 <= 节点个数 <= 1000

// -------------------第三次刷-----------------------
// 2021年5月13日10:38:49
// 准备第一次社招
// 思路: 再次中招, 这个对称的概念不仅仅是一个node的letf->val==right->val, 除此之外还有left->left->val==right->right->val&&left->right->val==right->left->val
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL)
    {
    }
};
class Solution {
public:
    bool isSymmetric_repeat(TreeNode* left, TreeNode* right) {
        if(left == nullptr && right == nullptr)
            return true;
        else if((left == nullptr && right != nullptr) || (left != nullptr && right == nullptr))
            return false;
        
        if(left->val == right->val){
            return isSymmetric_repeat(left->left, right->right) && isSymmetric_repeat(left->right, right->left);
        }
        else
            return false;
    }
    bool isSymmetric(TreeNode* root) {
        if(root==nullptr)
            return true;
        return isSymmetric_repeat(root->left, root->right);
    }
    // bool isSymmetric_repeat(TreeNode* root) {
    //     if( root == nullptr )
    //         return true;
        
    //     if(root->left && root->right){
    //         if(root->left->val == root->right->val)
    //             return isSymmetric_repeat(root->left) && isSymmetric_repeat(root->right);
    //         else
    //             return false;
    //     }
    //     else
    //         return false;
    // }
    // bool isSymmetric(TreeNode* root) {
    //     return isSymmetric_repeat(root);
    // }
};




//page 159
#include <iostream>
using namespace std;

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL)
    {
    }
};

class Solution
{
public:
    // bool isSymmetrical_repeat(TreeNode *pRoot1,TreeNode *pRoot2)
    // {
    //     if(pRoot1==nullptr&&pRoot2==nullptr)
    //         return true;
    //     if(pRoot1==nullptr||pRoot2==nullptr)
    //         return false;
    //     if(pRoot1->val!=pRoot2->val)
    //         return false;
    //     else
    //         return isSymmetrical_repeat(pRoot1->left,pRoot2->right)&&isSymmetrical_repeat(pRoot1->right,pRoot2->left);

    // }

    // bool isSymmetrical(TreeNode *pRoot)
    // {
    //     return isSymmetrical_repeat(pRoot,pRoot);
    // }
    
    bool isSymmetrical_repeat(TreeNode *pLeft,TreeNode *pRight)
    {
        if(pLeft==nullptr&&pRight==nullptr)
            return true;
        if(pLeft==nullptr&&pRight!=nullptr||(pLeft!=nullptr&&pRight==nullptr))
            return false;
        if(pLeft->val==pRight->val)
        {
            //所谓的镜像二叉树，不是说左节点的值等于右节点的值，而是如下
            return true&&isSymmetrical_repeat(pLeft->left,pRight->right)&&isSymmetrical_repeat(pLeft->left,pRight->right);
        }
        else
            return false;

    }
    bool isSymmetrical(TreeNode *pRoot)
    {
        if(pRoot==nullptr)
            return true;
        if(pRoot->left&&pRoot->right)
            return isSymmetrical_repeat(pRoot->left,pRoot->right);
        if(pRoot->left==nullptr&&pRoot->right==nullptr)
            return true;
        if(pRoot->left==nullptr||pRoot->right==nullptr)
            return false;
        return false;
    }
};