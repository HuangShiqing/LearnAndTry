// 538. 把二叉搜索树转换为累加树
// 给出二叉 搜索 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater Sum Tree），
// 使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。

// 提醒一下，二叉搜索树满足下列约束条件：

// 节点的左子树仅包含键 小于 节点键的节点。
// 节点的右子树仅包含键 大于 节点键的节点。
// 左右子树也必须是二叉搜索树。

// -------------------第二次刷-----------------------
// 2021年7月19日14:14:33
// 准备第一次社招
// 思路: 仔细读题应该蛮明确的. "等于原数中大于或等于 node.val 的值之和"不就是等于"右节点及其子节点的和". 那么这个dfs遍历
// 的顺序就是右节点, node, 左节点, 也就是所谓的反序中序遍历

//  * Definition for a binary tree node.
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int sum=0;
    TreeNode* convertBST(TreeNode* root) {
        if(root!=nullptr){
            convertBST(root->right);
            sum+=root->val;
            root->val =sum;
            convertBST(root->left);
        }
        return root;
    }
};