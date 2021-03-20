//page 148
#include <iostream>
using namespace std;

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL)
    {
    }
};

class Solution
{
public:
    // bool DoesTree1HaveTree2(TreeNode* pRoot1, TreeNode* pRoot2)
    // {
    //     if(pRoot2==nullptr)
    //         return true;
    //     if(pRoot1 == nullptr)
    //         return false;

    //     if(pRoot1->val != pRoot2->val)
    //         return false;

    //     return DoesTree1HaveTree2(pRoot1->left, pRoot2->left)&&DoesTree1HaveTree2(pRoot1->right, pRoot2->right);
    // }

    // bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    // {
    //     bool result = false;
    //     if(pRoot1 != nullptr&&pRoot2 != nullptr)
    //     {
    //         if(pRoot1->val == pRoot2->val)
    //         {
    //             result = DoesTree1HaveTree2(pRoot1,pRoot2);
    //         }
    //         if(!result)
    //             result = HasSubtree(pRoot1->left, pRoot2);
    //         if(!result)
    //             result = HasSubtree(pRoot1->right, pRoot2);
    //     }
    //     return result;
    // }
    //遍历判断是否能重合
    bool HasSubtree_repeat(TreeNode *pRoot1, TreeNode *pRoot2)
    {
        //当2为空时不管1是不是空，就是能重合
        if(pRoot2==nullptr)
            return true;
        //当2不是空但1已经是空的时候，就不能重合
        if(pRoot1==nullptr)
            return false;
        if(pRoot1->val==pRoot2->val)
            return HasSubtree_repeat(pRoot1->left, pRoot2->left)&&HasSubtree_repeat(pRoot1->right, pRoot2->right);
        return false;
    }

    bool HasSubtree_repeat2(TreeNode *pRoot1, TreeNode *pRoot2)
    {
        if (pRoot1 == nullptr)
            return false;
        //如果当前1能和2重合，返回ture
        if(HasSubtree_repeat(pRoot1, pRoot2))
            return true;
        //否则返回1的子节点能不能和2重合
        else
            return HasSubtree_repeat2(pRoot1->left, pRoot2)||HasSubtree_repeat2(pRoot1->right, pRoot2);
    }

    bool HasSubtree(TreeNode *pRoot1, TreeNode *pRoot2)
    {
        if (pRoot1 == nullptr || pRoot2==nullptr)
            return false;
        return HasSubtree_repeat2(pRoot1, pRoot2);
    }
};

int main()
{
    TreeNode a = TreeNode(2);
    cout << "hi" << endl;
}