#include <iostream>
#include <vector>
#include <stack>
#include <deque>
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
    // deque<TreeNode *> gd;
    // vector<vector<int>> gv;
    // vector<vector<int>> Print(TreeNode *pRoot)
    // {
    //     if (pRoot == nullptr)
    //         return gv;
    //     else
    //         gd.push_back(pRoot);

    //     TreeNode *pright = gd.back();
    //     vector<int> v;
    //     while (gd.size())
    //     {

    //         TreeNode *pNode = gd.front();
    //         gd.pop_front();
    //         v.push_back(pNode->val);

    //         if (pNode->left)
    //             gd.push_back(pNode->left);
    //         if (pNode->right)
    //             gd.push_back(pNode->right);

    //         if(pNode==pright)
    //         {
    //             gv.push_back(v);
    //             v.clear();
    //             if(gd.size())
    //                 pright=gd.back();
    //         }
    //     }
    //     return gv;
    // }

    vector<vector<int>> Print(TreeNode *pRoot)
    {
        vector<vector<int>> vv;
        vector<int> v;
        deque<TreeNode *> q1;
        deque<TreeNode *> q2;

        if (pRoot == nullptr)
            return vv;
        q1.push_back(pRoot);

        while (q1.size() || q2.size())
        {
            v.clear();
            while (q1.size())
            {
                TreeNode *node = q1.front();
                v.push_back(node->val);
                q1.pop_front();

                if (node->left)
                    q2.push_back(node->left);
                if (node->right)
                    q2.push_back(node->right);
            }
            if(v.size())
                vv.push_back(v);
            v.clear();
            while (q2.size())
            {
                TreeNode *node = q2.front();
                v.push_back(node->val);
                q2.pop_front();

                if (node->left)
                    q1.push_back(node->left);
                if (node->right)
                    q1.push_back(node->right);
            }
            if(v.size())
                vv.push_back(v);
        }
        return vv;
    }
};