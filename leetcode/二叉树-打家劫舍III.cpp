#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;


// 337. 打家劫舍 III
// 在上次打劫完一条街道之后和一圈房屋后，小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为“根”。 
// 除了“根”之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类
// 似于一棵二叉树”。 如果两个直接相连的房子在同一天晚上被打劫，房屋将自动报警。
// 计算在不触动警报的情况下，小偷一晚能够盗取的最高金额。

// 示例 1:
// 输入: [3,2,3,null,3,null,1]
//      3
//     / \
//    2   3
//     \   \ 
//      3   1
// 输出: 7 
// 解释: 小偷一晚能够盗取的最高金额 = 3 + 3 + 1 = 7.

// 示例 2:
// 输入: [3,4,5,1,3,null,1]
//      3
//     / \
//    4   5
//   / \   \ 
//  1   3   1
// 输出: 9
// 解释: 小偷一晚能够盗取的最高金额 = 4 + 5 = 9.

// -------------------第二次刷-----------------------
// 2021年7月6日10:56:38
// 准备第一次社招
// 思路: 制约条件是root节点和left, right之间的二选一关系, 打劫root节点, 则需要加上left, right没有被打劫时及其下面
// 子树的收益情况，那么这意味着这是一个后续遍历，深度优先。
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