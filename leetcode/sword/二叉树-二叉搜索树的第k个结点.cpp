#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <string>
#include <string.h>
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
    // vector<TreeNode *> gv;
    // //TODO:如何在找到目标节点时立马退出
    // void KthNode_repeat(TreeNode *pRoot)
    // {
    //     if (pRoot == nullptr)
    //         return;

    //     if (pRoot->left)
    //         KthNode_repeat(pRoot->left);

    //     gv.push_back(pRoot);

    //     if (pRoot->right)
    //         KthNode_repeat(pRoot->right);
    // }

    // TreeNode *KthNode(TreeNode *pRoot, int k)
    // {
    //     if (pRoot == nullptr || k <= 0)
    //         return nullptr;
    //     KthNode_repeat(pRoot);

    //     if(k>gv.size())
    //         return nullptr;
    //     return gv[k - 1];
    // }
    vector<TreeNode *> g_v;
    int g_k;
    void KthNode_repeat(TreeNode *pRoot)
    {
        if (pRoot == nullptr)
            return;
        if (pRoot->left)
            KthNode_repeat(pRoot->left);
        g_v.push_back(pRoot);
        // if(g_v.size()==g_k)
        //     return;
        if (pRoot->right)
            KthNode_repeat(pRoot->right);            
    }

    TreeNode *KthNode(TreeNode *pRoot, int k)
    {
        if (pRoot == nullptr||k<=0)
            return nullptr;
        KthNode_repeat(pRoot);
        if(k>g_v.size())
            return nullptr;
        return g_v[k-1];
    }
};