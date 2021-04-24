#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// dp[0][node]表示该node被打劫时, 该node与其子树所成的二叉树的最大值
// dp[0][node] = dp[node->left][1]+dp[node->right][1]+node->val, 左右子树要不被打劫

// dp[1][node]表示该node不被打劫时, 该node与其子树所成的二叉树的最大值
// dp[1][node] = max(dp[node->left][0],dp[node->left][1] )+max(dp[node->right][0], dp[node->right][1]),
// 左子树可以被打劫也可以不被打劫, 取最大值

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
class Solution {
public:
    vector<unordered_map<TreeNode*, int>> dp;

    void dfs(TreeNode* root) {
        if (root == nullptr)
            return;

        dfs(root->left);
        dfs(root->right);

        //当前的赋值依赖于子树, 因此是后序遍历
        dp[0][root] = dp[1][root->left] + dp[1][root->right] + root->val;
        dp[1][root] = max(dp[0][root->left], dp[1][root->left]) + max(dp[0][root->right], dp[1][root->right]);
    }

    int rob(TreeNode* root) {
        dp.resize(2);
        dfs(root);
        return max(dp[0][root], dp[1][root]);
    }
};