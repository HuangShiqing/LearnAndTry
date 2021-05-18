// 剑指 Offer 36. 二叉搜索树与双向链表
// 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。

// 为了让您更好地理解问题，以下面的二叉搜索树为例：
// 我们希望将这个二叉搜索树转化为双向循环链表。链表中的每个节点都有一个前驱和后继指针。对于双向循环链表，
// 第一个节点的前驱是最后一个节点，最后一个节点的后继是第一个节点。

// 下图展示了上面的二叉搜索树转化成的链表。“head” 表示指向链表中有最小元素的节点。

// 2021年05月16日10:41:49
// 准备第一次社招
// 思路: 递归, 目的是获得node转成双向链表后的head和tail, 退出条件是到最后一层的子叶节点. 
// 执行内容是把node插入到node->left递归出来的以及node->right递归出来的中间
// 但是这个指针参数好像有点问题

// 思路2: 遍历, 放到一个v里, 然后连起来

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

class Solution {
public:
    void treeToDoublyList(Node* root, Node* head, Node* tail){
        if(root->left==nullptr&&root->right==nullptr){
            head=root;
            tail=root;
            return;
        }

        if(root->left==nullptr){
            head = root;
        }
        else{
            Node* left_head;
            Node* left_tail;
            treeToDoublyList(root->left, left_head, left_tail);
            root->left = left_tail;
            if(left_tail)
                left_tail->right = root;
            head = left_head;
        }

        if(root->right==nullptr){
            tail = root;
        }
        else{
            Node* right_head;
            Node* right_tail;
            treeToDoublyList(root->right, right_head, right_tail);
            root->right = right_head;
            if(right_head)
                right_head->left = root;
            tail = right_tail;
        }    
    }

    Node* treeToDoublyList(Node* root) {
        if(root==nullptr)
            return nullptr;
        Node* head;
        Node* tail;
        treeToDoublyList(root, head, tail);
        head->left = tail;
        tail->right=head;
        return head;
    }
};


#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    // TreeNode(int x) : val(x), left(NULL), right(NULL)
    // {
    // }
};
// class Solution
// {
// public:
//     TreeNode *Convert_repeat(TreeNode *pfront, TreeNode *pRootOfTree)
//     {
//         // if (pRootOfTree->left != nullptr ||)
//         // {
//         // }
//         // if (pRootOfTree->right != nullptr)
//         // {
//         // }
//         TreeNode *pleft = pRootOfTree->left;
//         TreeNode *pright = pRootOfTree->right;
//         if (pleft != nullptr)
//         {
//             pfront = Convert_repeat(pfront, pleft);
//             pRootOfTree->left = pfront;
//             pfront->right = pRootOfTree;
//         }
//         else if (pfront == nullptr)
//         {
//             return pRootOfTree;
//         }
//         else
//         {
//             pfront->right = pRootOfTree;
//         }

//         if (pright != nullptr)
//         {
//             pfront = Convert_repeat(pRootOfTree, pright);
//             pRootOfTree->right =
//         }
//     }

//     TreeNode *Convert(TreeNode *pRootOfTree)
//     {

//         TreeNode * p = Convert_repeat(nullptr, pRootOfTree);
//     }
// };
class Solution
{
public:
    vector<TreeNode *> v;

    void Convert_repeat(TreeNode *pRootOfTree)
    {
        TreeNode *pleft = pRootOfTree->left;
        TreeNode *pright = pRootOfTree->right;
        if (pleft != nullptr)
        {
            Convert_repeat(pleft);
        }

        v.push_back(pRootOfTree);
        if (pright != nullptr)
        {
            Convert_repeat(pright);
        }
    }

    TreeNode *Convert(TreeNode *pRootOfTree)
    {
        if(pRootOfTree==nullptr)
            return pRootOfTree;

        Convert_repeat(pRootOfTree);

        if(v.size()==1)
            return pRootOfTree;

        for (int i = 0; i < v.size(); i++)
        {
            if (i == 0)
            {
                v[0]->left = nullptr;
                v[0]->right = v[1];
            }
            else if (i == (v.size() - 1))
            {
                v[v.size() - 1]->left = v[v.size() - 2];
                v[v.size() - 1]->right = nullptr;
            }
            else
            {
                v[i]->left = v[i - 1];
                v[i]->right = v[i + 1];
            }
        }
        return v[0];
    }
};

int main()
{
    TreeNode *ptree_root = new TreeNode;
    ptree_root->val = 10;
    // ptree_root->left = new TreeNode;
    // ptree_root->left->val = 6;
    // ptree_root->right = new TreeNode;
    // ptree_root->right->val = 14;
    // ptree_root->left->left = new TreeNode;
    // ptree_root->left->left->val = 4;
    // ptree_root->left->right = new TreeNode;
    // ptree_root->left->right->val = 8;
    // ptree_root->right->left = new TreeNode;
    // ptree_root->right->left->val = 12;
    // ptree_root->right->right = new TreeNode;
    // ptree_root->right->right->val = 16;
    Solution solution;
    solution.Convert(ptree_root);
}