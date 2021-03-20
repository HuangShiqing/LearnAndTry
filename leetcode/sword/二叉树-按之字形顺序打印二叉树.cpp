//page 176
#include <iostream>
#include <vector>
#include <stack>
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
    // stack<TreeNode *> s1;
    // stack<TreeNode *> s2;
    // vector<vector<int>> v;
    // int depth = 1;

    // void Print_repeat()
    // {
    //     if (depth % 2 == 1)
    //     {
    //         vector<int> v1;
    //         while (s1.size())
    //         {
    //             TreeNode *pNode = s1.top();
    //             s1.pop();
    //             v1.push_back(pNode->val);

    //             if(pNode->left)
    //                 s2.push(pNode->left);
    //             if(pNode->right)
    //                 s2.push(pNode->right);
    //         }
    //         v.push_back(v1);

    //         if(s2.empty()==false)
    //         {
    //             depth++;
    //             Print_repeat();
    //         }
    //     }
    //     else
    //     {
    //         vector<int> v2;
    //         while(s2.size())
    //         {
    //             TreeNode *pNode = s2.top();
    //             s2.pop();
    //             v2.push_back(pNode->val);

    //             if(pNode->right)
    //                 s1.push(pNode->right);
    //             if(pNode->left)
    //                 s1.push(pNode->left);
    //         }
    //         v.push_back(v2);

    //         if(s1.empty()==false)
    //         {
    //             depth++;
    //             Print_repeat();
    //         }

    //     }

    // }
    // vector<vector<int>> Print(TreeNode *pRoot)
    // {
    //     if (pRoot == nullptr)
    //         return v;
    //     s1.push(pRoot);
    //     depth = 1;
    //     Print_repeat();
    //     return v;
    // }

    vector<vector<int>> Print(TreeNode *pRoot)
    {
        vector<vector<int>> vv;
        vector<int> v;
        stack<TreeNode *> s1;
        stack<TreeNode *> s2;
        if (pRoot == nullptr)
            return vv;

        s1.push(pRoot);
        //用2个独立的栈来保存各层的节点
        while (s1.size() || s2.size())
        {
            v.clear();
            while (s1.size())
            {
                TreeNode *node = s1.top();
                s1.pop();
                v.push_back(node->val);
                if (node->left)
                    s2.push(node->left);
                if (node->right)
                    s2.push(node->right);
            }
            if(v.size())
                vv.push_back(v);

            v.clear();
            while (s2.size())
            {
                TreeNode *node = s2.top();
                s2.pop();
                v.push_back(node->val);
                //第二行要反着push
                if (node->right)
                    s1.push(node->right);
                if (node->left)
                    s1.push(node->left);                
            }
            if(v.size())
                vv.push_back(v);
        }
        return vv;
    }
};