// 剑指 Offer 26. 树的子结构
// 输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)
// B是A的子结构， 即 A中有出现和B相同的结构和节点值。

// 例如:
// 给定的树 A:
//      3
//     / \
//    4   5
//   / \
//  1   2
// 给定的树 B：
//    4 
//   /
//  1
// 返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。

// 示例 1：
// 输入：A = [1,2,3], B = [3,1]
// 输出：false

// 示例 2：
// 输入：A = [3,4,5,1,2], B = [4,1]
// 输出：true
// 限制：
// 0 <= 节点个数 <= 10000

// -------------------第三次刷-----------------------
// 2021年5月13日10:38:49
// 准备第一次社招
// 思路: 递归. 如果当前节点就相等, 则递归判断Ab的左右子树是否都相等. 如果当前节点不相等, 则递归判断A的左右子树里是否至少有一个与B相等的. 
// 根本的true or false来自于最深的子节点, 根本的true来自于当B为空而A空不空都可以, false来自于A为空而B不为空

// 这题不简单的!!!!!!!!!!
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    bool isSubStructure_repeat(TreeNode* A, TreeNode* B) {
        if(B==nullptr)
            return true;
        else if(A == nullptr && B!= nullptr)
            return false;

        // if(A->val == B->val) {
        //     return isSubStructure_repeat(A->left, B->left) && isSubStructure_repeat(A->right, B->right);
        // }
        // else
        //     return false;

        // bool r = false;
        // if(A->val == B->val) 
        //     r =  isSubStructure_repeat(A->left, B->left) && isSubStructure_repeat(A->right, B->right);
        // if(r == false)
        //     r =  isSubStructure_repeat(A->left, B) || isSubStructure_repeat(A->right, B);
        // return r;

        // if(A->val == B->val) {
        //     return isSubStructure_repeat(A->left, B->left) && isSubStructure_repeat(A->right, B->right);
        // }
        // else{
        //     return isSubStructure_repeat(A->left, B) || isSubStructure_repeat(A->right, B);
        // }
    }


    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if(A ==nullptr || B == nullptr)//约定空树不是任意一个树的子结构
            return false;

        return isSubStructure_repeat(A, B) || ;
    }
};

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