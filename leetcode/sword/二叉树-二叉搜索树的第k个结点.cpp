// 剑指 Offer 54. 二叉搜索树的第k大节点
// 给定一棵二叉搜索树，请找出其中第k大的节点。

// 示例 1:
// 输入: root = [3,1,4,null,2], k = 1
//    3
//   / \
//  1   4
//   \
//    2
// 输出: 4

// 示例 2:
// 输入: root = [5,3,6,2,4,null,null,1], k = 3
//        5
//       / \
//      3   6
//     / \
//    2   4
//   /
//  1
// 输出: 4

// -------------------第三次刷-----------------------
// 2021年6月1日10:04:34
// 准备第一次社招
// 思路: 很简单, 中序遍历即可

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> v;
    void kthLargest(TreeNode* root){
        if(root==nullptr)
            return;
        
        kthLargest(root->left);
        v.push_back(root->val);
        kthLargest(root->right);
    }
    int kthLargest(TreeNode* root, int k) {
        kthLargest(root);
        if(v.size()>=k)
            return v[v.size()-k];
        else
            return -1;s
    }
};


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