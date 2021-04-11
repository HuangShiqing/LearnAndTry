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
    //有点问题,但是不知道在哪里
    // void mergeTrees_repeat(TreeNode* root1, TreeNode* root2, TreeNode* root3) {
    //     if (root1 == nullptr && root2 == nullptr) {
    //         return;
    //     }

    //     bool flag_left = true;
    //     bool flag_right = true;
    //     if (root1 == nullptr) {
    //         root3->val = root2->val;
    //         flag_left = flag_left && (root2->left);
    //         flag_right = flag_right && (root2->right);
    //     } else if (root2 == nullptr) {
    //         root3->val = root1->val;
    //         flag_left = flag_left && (root1->left);
    //         flag_right = flag_right && (root1->right);
    //     } else {
    //         root3->val = root1->val + root2->val;
    //         flag_left = flag_left && (root1->left || root2->left);
    //         flag_right = flag_right && (root1->right || root2->right);
    //     }

    //     if (flag_left) {
    //         TreeNode* new_left = new TreeNode();
    //         root3->left = new_left;
    //         mergeTrees_repeat(root1 ? root1->left : nullptr, root2 ? root2->left : nullptr, root3->left);
    //     }
    //     if (flag_right) {
    //         TreeNode* new_right = new TreeNode();
    //         root3->right = new_right;
    //         mergeTrees_repeat(root1 ? root1->left : nullptr, root2 ? root2->left : nullptr, root3->right);
    //     }
    // }

    // TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    //     if (root1 == nullptr && root2 == nullptr)
    //         return nullptr;

    //     TreeNode* merged = new TreeNode();
    //     // merged->val = root1 ? root1->val : 0 + root2 ? root2->val : 0;

    //     mergeTrees_repeat(root1, root2, merged);
    //     return merged;
    // }

    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        //如果有一个为nullptr,那都不用新建了,直接返回另外一个连上即可
        if (root1 == nullptr) {
            return root2;
        }
        if (root2 == nullptr) {
            return root1;
        }
        auto merged = new TreeNode(root1->val + root2->val);
        merged->left = mergeTrees(root1->left, root2->left);
        merged->right = mergeTrees(root1->right, root2->right);
        return merged;
    }
};