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