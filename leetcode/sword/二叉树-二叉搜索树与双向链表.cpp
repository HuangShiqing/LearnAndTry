#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    // TreeNode(int x) : val(x), left(NULL), right(NULL)
    // {
    // }
};
// class Solution
// {
// public:
//     TreeNode *Convert_repeat(TreeNode *pfront, TreeNode *pRootOfTree)
//     {
//         // if (pRootOfTree->left != nullptr ||)
//         // {
//         // }
//         // if (pRootOfTree->right != nullptr)
//         // {
//         // }
//         TreeNode *pleft = pRootOfTree->left;
//         TreeNode *pright = pRootOfTree->right;
//         if (pleft != nullptr)
//         {
//             pfront = Convert_repeat(pfront, pleft);
//             pRootOfTree->left = pfront;
//             pfront->right = pRootOfTree;
//         }
//         else if (pfront == nullptr)
//         {
//             return pRootOfTree;
//         }
//         else
//         {
//             pfront->right = pRootOfTree;
//         }

//         if (pright != nullptr)
//         {
//             pfront = Convert_repeat(pRootOfTree, pright);
//             pRootOfTree->right =
//         }
//     }

//     TreeNode *Convert(TreeNode *pRootOfTree)
//     {

//         TreeNode * p = Convert_repeat(nullptr, pRootOfTree);
//     }
// };
class Solution
{
public:
    vector<TreeNode *> v;

    void Convert_repeat(TreeNode *pRootOfTree)
    {
        TreeNode *pleft = pRootOfTree->left;
        TreeNode *pright = pRootOfTree->right;
        if (pleft != nullptr)
        {
            Convert_repeat(pleft);
        }

        v.push_back(pRootOfTree);
        if (pright != nullptr)
        {
            Convert_repeat(pright);
        }
    }

    TreeNode *Convert(TreeNode *pRootOfTree)
    {
        if(pRootOfTree==nullptr)
            return pRootOfTree;

        Convert_repeat(pRootOfTree);

        if(v.size()==1)
            return pRootOfTree;

        for (int i = 0; i < v.size(); i++)
        {
            if (i == 0)
            {
                v[0]->left = nullptr;
                v[0]->right = v[1];
            }
            else if (i == (v.size() - 1))
            {
                v[v.size() - 1]->left = v[v.size() - 2];
                v[v.size() - 1]->right = nullptr;
            }
            else
            {
                v[i]->left = v[i - 1];
                v[i]->right = v[i + 1];
            }
        }
        return v[0];
    }
};

int main()
{
    TreeNode *ptree_root = new TreeNode;
    ptree_root->val = 10;
    // ptree_root->left = new TreeNode;
    // ptree_root->left->val = 6;
    // ptree_root->right = new TreeNode;
    // ptree_root->right->val = 14;
    // ptree_root->left->left = new TreeNode;
    // ptree_root->left->left->val = 4;
    // ptree_root->left->right = new TreeNode;
    // ptree_root->left->right->val = 8;
    // ptree_root->right->left = new TreeNode;
    // ptree_root->right->left->val = 12;
    // ptree_root->right->right = new TreeNode;
    // ptree_root->right->right->val = 16;
    Solution solution;
    solution.Convert(ptree_root);
}