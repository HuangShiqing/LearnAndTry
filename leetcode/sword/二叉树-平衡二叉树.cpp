
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
