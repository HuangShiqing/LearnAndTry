// 剑指 Offer 68 - I. 二叉搜索树的最近公共祖先

// 给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
// 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
// 例如，给定如下二叉搜索树:  root = [6,2,8,0,4,7,9,null,null,3,5]

// 示例 1:
// 输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
// 输出: 6 
// 解释: 节点 2 和节点 8 的最近公共祖先是 6。

// 示例 2:
// 输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
// 输出: 2
// 解释: 节点 2 和节点 4 的最近公共祖先是 2, 因为根据定义最近公共祖先节点可以为节点本身。

// 说明:
// 所有节点的值都是唯一的。
// p、q 为不同节点且均存在于给定的二叉搜索树中。

// -------------------第三次刷-----------------------
// 2021年06月05日10:28:23
// 准备第一次社招
// 思路1: 二叉搜索树的特点是左边的小于root, 右边的大于root. 所以当pq都小于某个node root时, 那么该
// node肯定是公共祖先节点, 但不是最近的. 最近的肯定是p和q在node的两边. 
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(p.val<root->val&&q.val<root->val)
            return lowestCommonAncestor(root->left, p, q);

        if(p.val>root->val&&q.val>root->val)
            return lowestCommonAncestor(root->right, p, q);        
        return root;
    }
};

#include <vector>
using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 思路2: 保存遍历的路径也可以. 返回最后一个相等的node即可
class Solution {
public:
    vector<TreeNode*> path;
    vector<TreeNode*> path2;

    vector<TreeNode*> tmp;
    void lowestCommonAncestor_repeat(TreeNode* root, TreeNode* p, TreeNode* q){
        if(root==nullptr)
            return;
        
        tmp.push_back(root);
        if(root==p||root==q){
            if(path.size()==0)
                path = tmp;
            else if(path2.size()==0)
                path2 = tmp;
            else
                return;
        }
        lowestCommonAncestor_repeat(root->left, p, q);
        lowestCommonAncestor_repeat(root->right, p, q);
        tmp.pop_back();
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        lowestCommonAncestor_repeat(root, p, q);

        TreeNode* ret = nullptr;
        for(int i=0;i<min(path.size(), path2.size());i++)
            if(path[i]==path2[i])
                ret=path[i];
        
        return ret;
    }
};
