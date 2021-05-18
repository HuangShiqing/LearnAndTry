// 剑指 Offer 32 - II. 从上到下打印二叉树 II
// 从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。

// 例如:
// 给定二叉树: [3,9,20,null,null,15,7],
//     3
//    / \
//   9  20
//     /  \
//    15   7
// 返回其层次遍历结果：
// [
//   [3],
//   [9,20],
//   [15,7]
// ]

// -------------------第三次刷-----------------------
// 2021年05月15日10:17:39
// 准备第一次社招
// 思路: 用d1.size()来判断是要处理d1还是d2而不是用奇偶数行. 不要用递归了, 直接两层while来的简单
#include <vector>
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
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> vv;
		deque<TreeNode*> d1;
        deque<TreeNode*> d2;
		if(root==nullptr)
			return vv;

		d1.push_back(root);
		
        vector<int> v;
        while(d1.size()||d2.size()){
            v.clear();
            while(d1.size()) {
                if(d1.front()){
                    v.push_back(d1.front()->val);
                    d2.push_back(d1.front()->left);
                    d2.push_back(d1.front()->right);
                }
                d1.pop_front();
            }
            if(v.size())
                vv.push_back(v);
            
            v.clear();
            while(d2.size()) {
                if(d2.front()){
                    v.push_back(d2.front()->val);
                    d1.push_back(d2.front()->left);
                    d1.push_back(d2.front()->right);
                }
                d2.pop_front();
            }
            if(v.size())
                vv.push_back(v);
        }

		return vv;        
    }
};


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