// 剑指 Offer 68 - II. 二叉树的最近公共祖先
// 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

// 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

// 例如，给定如下二叉树:  root = [3,5,1,6,2,0,8,null,null,7,4]

// 示例 1:
// 输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
// 输出: 3
// 解释: 节点 5 和节点 1 的最近公共祖先是节点 3。

// 示例 2:
// 输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
// 输出: 5
// 解释: 节点 5 和节点 4 的最近公共祖先是节点 5。因为根据定义最近公共祖先节点可以为节点本身。
 
// 说明:
// 所有节点的值都是唯一的。
// p、q 为不同节点且均存在于给定的二叉树中。

// -------------------第三次刷-----------------------
// 2021年06月05日10:28:23
// 准备第一次社招
// 思路: 保存遍历的路径也可以. 返回最后一个相等的node即可
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

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