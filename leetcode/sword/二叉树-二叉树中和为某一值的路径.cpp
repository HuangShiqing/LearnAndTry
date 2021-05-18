// 剑指 Offer 34. 二叉树中和为某一值的路径
// 输入一棵二叉树和一个整数，打印出二叉树中节点值的和为输入整数的所有路径。
// 从树的根节点开始往下一直到叶节点所经过的节点形成一条路径。

// 示例:
// 给定如下二叉树，以及目标和 target = 22，

//               5
//              / \
//             4   8
//            /   / \
//           11  13  4
//          /  \    / \
//         7    2  5   1
// 返回:
// [
//    [5,4,11,2],
//    [5,8,4,5]
// ]

// 2021年05月15日21:35:29
// 准备第一次社招
// 思路: 满中规中矩的回溯. 就是需要注意路径要到底, 叶节点, 即left==nullptr&&right==nullotr

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

    void pathSum(TreeNode* root, vector<vector<int>>& vv, vector<int>& v, int& value, int target){
        if(!root)
            return;
        
        value += root->val;
        v.push_back(root->val);
        if(value==target && root->left==nullptr && root->right==nullptr)//路径要到底, 叶节点
            vv.push_back(v);

        pathSum(root->left, vv, v, value, target);
        pathSum(root->right, vv, v, value, target);

        value-= root->val;
        v.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int target) {
        vector<vector<int>> vv;
        vector<int> v;
        int value=0;
        pathSum(root, vv, v, value, target);
        return vv;
    }
};

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    // TreeNode(int x) :
    // 		val(x), left(NULL), right(NULL) {
    // }
};
class Solution
{
    // vector<TreeNode*> path;
    // int sum=0;
    // vector<vector<int> > result;

public:
    // void FindPath_repeat(TreeNode* root,int expectNumber)
    // {
    //     sum += root->val;
    //     path.push_back(root);

    //     bool isLeaf = root->left==nullptr&&root->right==nullptr;
    //     if(sum==expectNumber && isLeaf)
    //     {
    //         vector<int> result_temp;
    //         for(int i=0;i<path.size();i++)
    //             result_temp.push_back(path[i]->val);
    //         result.push_back(result_temp);
    //     }

    //     if(root->left!=nullptr)
    //         FindPath_repeat(root->left, expectNumber);
    //     if(root->right!=nullptr)
    //         FindPath_repeat(root->right, expectNumber);

    //     path.pop_back();
    //     sum -= root->val;

    // }

    // vector<vector<int> > FindPath(TreeNode* root,int expectNumber)
    // {
    //     if(root==nullptr)
    //         return result;
    //     FindPath_repeat(root, expectNumber);
    //     return result;

    // }
    //回溯法
    vector<vector<int>> vv;
    vector<int> v;
    int sum;
    int g_k;
    void FindPath_repeat(TreeNode *root)
    {
        //进一个节点就操作标记
        v.push_back(root->val);
        sum += root->val;
        //最终步的条件
        if (root->left == nullptr && root->left == nullptr)
        {
            // int sum=0;
            // for (int i = 0; i < v.size(); i++)
            //     sum += v[i];
            //满足条件的操作
            if (sum == g_k)
                vv.push_back(v);
        }
        //下一步递归
        if (root->left)
            FindPath_repeat(root->left);
        //下一步递归
        if (root->right)
            FindPath_repeat(root->right);
        //退出当前节点就清空标记
        v.pop_back();
        sum -= root->val;
    }
    static bool cmp_fun(vector<int> v1, vector<int> v2)
    {
        //前者小于后者成立则为升序
        if (v1.size() > v2.size())
            return true;
        else
            return false;
    }
    vector<vector<int>> FindPath(TreeNode *root, int expectNumber)
    {
        if (root == nullptr || expectNumber <= 0)
            return vv;
        g_k = expectNumber;
        sum = 0;
        FindPath_repeat(root);
        sort(vv.begin(),vv.end(),cmp_fun);
        return vv;
    }
};

int main()
{
    TreeNode *ptree_root = new TreeNode;
    ptree_root->val = 10;
    ptree_root->left = new TreeNode;
    ptree_root->left->val = 5;
    ptree_root->right = new TreeNode;
    ptree_root->right->val = 12;
    ptree_root->left->left = new TreeNode;
    ptree_root->left->left->val = 4;
    ptree_root->left->right = new TreeNode;
    ptree_root->left->right->val = 7;
    // ptree_root->right->left = new TreeNode;
    // ptree_root->right->left->val = 9;
    // ptree_root->right->right = new TreeNode;
    // ptree_root->right->right->val = 11;

    Solution solution;

    vector<vector<int>> result = solution.FindPath(ptree_root, 22);
    return 0;
}