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

class Solution {
public:
    vector<TreeNode*> v;
    void flatten_repeat(TreeNode* root) {
        v.push_back(root);
        if (root->left)
            flatten_repeat(root->left);
        if (root->right)
            flatten_repeat(root->right);
    }
    void flatten(TreeNode* root) {
        if (root == nullptr)
            return;
        flatten_repeat(root);

        TreeNode* pre=nullptr;
        TreeNode* cur = nullptr;
        for (int i = 1; i < v.size(); i++) {
            pre = v.at(i - 1);
            cur =  v.at(i);
            pre->left = nullptr;
            pre->right = cur;
        }

    }
};