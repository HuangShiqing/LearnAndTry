// page 62
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    TreeNode* reConstructBinaryTree_repeat(vector<int> pre, vector<int> vin, int pre_left, int pre_right, int in_left,
                                           int in_right) {
        TreeNode* root = new TreeNode(pre[pre_left]);
        //当只有一个值时，即该值作为最底层的root，不再递归
        if (pre_left == pre_right) {
            return root;
        }

        int root_index = in_left;
        while (vin[root_index] != pre[pre_left])
            root_index++;

        int new_left_length = root_index - in_left;
        int new_right_length = in_right - root_index;

        if (new_left_length > 0) {
            root->left = reConstructBinaryTree_repeat(pre, vin, pre_left + 1, pre_left + new_left_length, in_left,
                                                      root_index - 1);
        }
        if (new_right_length > 0) {
            root->right = reConstructBinaryTree_repeat(pre, vin, pre_left + 1 + new_left_length, pre_right,
                                                       root_index + 1, in_right);
        }
        return root;
    }

    TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin) {
        if (pre.size() == 0 || vin.size() == 0)
            return nullptr;

        return reConstructBinaryTree_repeat(pre, vin, 0, pre.size() - 1, 0, vin.size() - 1);
    }
};

// 剑指 Offer 07. 重建二叉树
// 输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

// 例如，给出
// 前序遍历 preorder = [3,9,20,15,7]
// 中序遍历 inorder = [9,3,15,20,7]
// 返回如下的二叉树：
//     3
//    / \
//   9  20
//     /  \
//    15   7

// 2021年04月24日15:22:50
// 准备第一次社招
// 思路:
// pre的第一个元素是root节点, 在in里找到该root, 其左右的数量即为左右子树的元素个数,
// 用这个left_size和right_size重新建立下一轮循环的输入
// 注意递归的条件为left_size>0, 如果left_size==1, 则下一轮可直接返回node

class Solution {
public:
    TreeNode* buildTree_repeat(vector<int>& preorder, vector<int>& inorder, int pre_left, int pre_right, int in_left,
                               int in_right) {
        TreeNode* node = new TreeNode(preorder[pre_left]);

        //当只有一个值时，即该值作为最底层的root，不再递归
        if (pre_left == pre_right) {
            return node;
        }

        int node_inorder_index = in_left;
        while (inorder[node_inorder_index] != preorder[pre_left]) {
            node_inorder_index++;
        }
        int left_size = node_inorder_index - in_left;
        int right_size = in_right - node_inorder_index;

        if (left_size > 0)
            node->left = buildTree_repeat(preorder, inorder, pre_left + 1, pre_left + 1 + left_size - 1, in_left,
                                          in_left + left_size - 1);
        if (right_size > 0)
            node->right = buildTree_repeat(preorder, inorder, pre_right - right_size + 1, pre_right,
                                           in_right - right_size + 1, in_right);
        return node;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0 || inorder.size() == 0)
            return nullptr;
        return buildTree_repeat(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }
};