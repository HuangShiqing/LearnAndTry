#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// 我觉得思路很简单啊, 找到两条对应的路径放到vector里. 然后找到index最大的相等元素.
// 为啥不对呢, 为啥题解里没人说这个思路呢
class Solution {
public:
    vector<TreeNode*> path1;
    vector<TreeNode*> path2;
    int dfs(TreeNode* root, TreeNode* p, TreeNode* q, int flag) {
        if (root == nullptr)
            return flag;

        if (flag == 0) {
            path1.push_back(root);
            path2.push_back(root);
        } else if (flag == 1) {
            path2.push_back(root);
        }
        if (root == p || root == q) {
            flag++;
            if (flag == 2)
                return flag;
        }

        flag = dfs(root->left, p, q, flag);
        if (flag == 2)
            return flag;
        else if (flag == 1) {
            path2.pop_back();
        } else if (flag == 0) {
            path1.pop_back();
            path2.pop_back();
        }
        flag = dfs(root->right, p, q, flag);
        if (flag == 2)
            return flag;
        else if (flag == 1) {
            path2.pop_back();
        } else if (flag == 0) {
            path1.pop_back();
            path2.pop_back();
        }

        return flag;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (dfs(root, p, q, 0) == 2) {
            int len1 = path1.size();
            int len2 = path2.size();
            int maxindex = 0;
            for (int i = 0; i < min(len1, len2); i++) {
                if (path1[i] == path2[i])
                    maxindex = i;
            }
            return path1[maxindex];

        } else
            return nullptr;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == q || root == p || root == NULL)
            return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left != NULL && right != NULL)
            return root;
        else if (left == NULL && right != NULL)
            return right;
        else if (left == NULL && right == NULL)
            return left;
    }
};