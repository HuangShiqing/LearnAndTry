// 剑指 Offer 55 - II. 平衡二叉树
// 输入一棵二叉树的根节点，判断该树是不是平衡二叉树。如果某二叉树中任意节点的左右子树的深度相差不超过1，那么它就是一棵平衡二叉树。

// 示例 1:
// 给定二叉树 [3,9,20,null,null,15,7]

//     3
//    / \
//   9  20
//     /  \
//    15   7
// 返回 true 。

// 示例 2:
// 给定二叉树 [1,2,2,3,3,null,null,4,4]

//        1
//       / \
//      2   2
//     / \
//    3   3
//   / \
//  4   4
// 返回 false 。

// -------------------第三次刷-----------------------
// 2021年6月1日15:18:44
// 准备第一次社招
// 思路1: 为true的条件是abs(left_depth-right_depth) && left为true && right为true. 但是这样意味着每处理一个node时还需要处理其left和right node. 这样会带来重复的计算深度
// 注意: 求深度两种思路都是从下到上, 都需要遍历一遍每个node的深度, 这个求深度的过程本身就有重复计算过程.

class Solution {
public:
    int getDepth(TreeNode* root){
        if(root==nullptr)
            return 0;
        
        int left = getDepth(root->left);
        int right = getDepth(root->right);

        return left>right?left+1:right+1;
    }

    bool isBalanced(TreeNode* root) {
        if (root == nullptr)
            return true;

        int left = getDepth(root->left);
        int right = getDepth(root->right);

        return abs(left-right)<=1 && isBalanced(root->left)&&isBalanced(root->right);
    }
};

//思路2: 求深度函数的返回值除了代表为深度外还代表其left和right是否都为平衡二叉树(-1代表不是). 处理一个node时只需要处理该node即可
// 注意: 求深度两种思路都是从下到上, 都需要遍历一遍每个node的深度, 这个求深度的过程本身就有重复计算过程.
class Solution {
public:
    int getDepth(TreeNode* root){
        if(root==nullptr)
            return 0;
        
        int left = getDepth(root->left);
        if(left==-1)
            return -1;

        int right = getDepth(root->right);
        if(right==-1)
            return -1;

        if(abs(left-right)<=1)
            return left>right?left+1:right+1;
        else
            return -1;
    }

    bool isBalanced(TreeNode* root) {

        return getDepth(root)==-1?false:true;
    }
};


//page 273
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    // TreeNode(int x) :
    // 		val(x), left(NULL), right(NULL) {
    // }
};

class Solution
{
public:
    // int TreeDepth(TreeNode* pRoot)
    // {
    //     if(pRoot==nullptr)
    //         return 0;
    //     int left = TreeDepth(pRoot->left);
    //     int right = TreeDepth(pRoot->right);
    //     return (left>right)?(left+1):(right+1);
    // }
    // int IsBalanced_Solution(TreeNode* pRoot)
    // {
    //     if(pRoot==nullptr)
    //         return true;
    //     int left = IsBalanced_Solution(pRoot->left);
    //     int right = IsBalanced_Solution(pRoot->right);
    //     int diff=left-right;
    //     if(diff>1||diff<-1)
    //         return false;
    //     return IsBalanced_Solution(pRoot->left)&&IsBalanced_Solution(pRoot->right);
    // }

    int TreeDepth(TreeNode *pRoot)
    {
        if (pRoot == nullptr)
            return 0;

        int left = TreeDepth(pRoot->left);
        int right = TreeDepth(pRoot->right);

        return (left > right) ? (left + 1) : (right + 1);
    }

    bool IsBalanced_Solution(TreeNode *pRoot)
    {
        if (pRoot == nullptr)
            return true;

        int left = TreeDepth(pRoot->left);
        int right = TreeDepth(pRoot->right);
        if((left-right)>1||(left-right)<-1)
        //平衡二叉树是左右子树深度相差不超过1，不是说要一定一样
            return false;
        //是平衡二叉树的条件是不超过1并且左右子树也都是平衡二叉树
        return IsBalanced_Solution(pRoot->left) && IsBalanced_Solution(pRoot->right);
    }



};
