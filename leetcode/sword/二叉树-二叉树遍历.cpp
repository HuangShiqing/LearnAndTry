#include <iostream>
#include <vector>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

vector<int> v;

void front_scanf(TreeNode *pRoot)
{
    if (pRoot == nullptr)
        return;

    v.push_back(pRoot->val);

    if (pRoot->left)
        front_scanf(pRoot->left);
    if (pRoot->right)
        front_scanf(pRoot->right);
}

void middle_scanf(TreeNode *pRoot)
{
    if (pRoot == nullptr)
        return;

    if (pRoot->left)
        middle_scanf(pRoot->left);
    v.push_back(pRoot->val);
    if (pRoot->right)
        middle_scanf(pRoot->right);
}

void back_scanf(TreeNode *pRoot)
{
    if (pRoot == nullptr)
        return;

    if (pRoot->left)
        back_scanf(pRoot->left);

    if (pRoot->right)
        back_scanf(pRoot->right);
    v.push_back(pRoot->val);
}

int main()
{
    TreeNode *pRoot = new TreeNode(5);
    pRoot->left = new TreeNode(3);
    pRoot->right = new TreeNode(7);

    pRoot->left->left = new TreeNode(2);
    pRoot->left->right = new TreeNode(4);

    pRoot->right->left = new TreeNode(6);
    pRoot->right->right = new TreeNode(8);

    // front_scanf(pRoot);
    // middle_scanf(pRoot);
    back_scanf(pRoot);

    return 0;
}