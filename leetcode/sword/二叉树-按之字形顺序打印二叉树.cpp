// 剑指 Offer 32 - III. 从上到下打印二叉树 III
// 请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。

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
//   [20,9],
//   [15,7]
// ]

// -------------------第三次刷-----------------------
// 2021年05月15日10:17:39
// 准备第一次社招
// 思路: 跟上一题一样, 但是这里每次就不是先进先出, 而是先进后出, 就应该想到
// 把deque换成stack. 
// 注意: s2需要先push right

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
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> vv;
		stack<TreeNode*> s1;
        stack<TreeNode*> s2;
		if(root==nullptr)
			return vv;

		s1.push(root);
		
        vector<int> v;
        while(s1.size()||s2.size()){
            v.clear();
            while(s1.size()) {
                if(s1.top()){
                    v.push_back(s1.top()->val);
                    s2.push(s1.top()->left);
                    s2.push(s1.top()->right);
                }
                s1.pop();
            }
            if(v.size())
                vv.push_back(v);
            
            v.clear();
            while(s2.size()) {
                if(s2.top()){
                    v.push_back(s2.top()->val);
                    //s2需要先push right
                    s1.push(s2.top()->right);
                    s1.push(s2.top()->left);
                }
                s2.pop();
            }
            if(v.size())
                vv.push_back(v);
        }

		return vv;        
    }
};


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