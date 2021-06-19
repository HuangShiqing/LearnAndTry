#include <iostream>
#include <vector>
using namespace std;

// 114. 二叉树展开为链表
// 给你二叉树的根结点 root ，请你将它展开为一个单链表：
// 展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
// 展开后的单链表应该与二叉树 先序遍历 顺序相同。
 
// 示例 1：
// 输入：root = [1,2,5,3,4,null,6]
// 输出：[1,null,2,null,3,null,4,null,5,null,6]

// 示例 2：
// 输入：root = []
// 输出：[]

// 示例 3：
// 输入：root = [0]
// 输出：[0]

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// 2021年6月18日10:25:35
// 准备第一次社招
// 思路1: 先序遍历保存后再换成链表. 有点无脑
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

// 2021年6月18日10:25:35
// 准备第一次社招
// 思路2: 原地转变. 类似链表反转. 需要多看看
class Solution {
    void flatten(TreeNode* root) {
        if (root == nullptr) 
            return;
        //1.先变左边
        flatten(root->left);
        //2.将root的左右都设置好. 记得先保存root->right
        TreeNode* old_right = root->right;
        root->right = root->left;
        root->left = nullptr;
        //3.转变右边
        flatten(old_right);
        //4.找到刚才left的最右边, 然后接上3刚转好的右边. 即root的左子树的链表尾接的是右子树的头
        while (root->right != nullptr) {
            root = root->right;
        }        
        root->right = old_right;
    }
}