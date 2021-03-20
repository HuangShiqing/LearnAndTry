
//page 271
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

    // int depth=0;
    // int max_depth=0;
    // void TreeDepth_repeat(TreeNode* pRoot)
    // {
    //     //进来深度加1
    //     depth++;
    //     if(depth>max_depth)
    //         max_depth=depth;

    //     if(pRoot->left)
    //         TreeDepth_repeat(pRoot->left);
    //     if(pRoot->right)
    //         TreeDepth_repeat(pRoot->right);
    //     //准备退出了深度减一
    //     depth--;
    // }
    // int TreeDepth(TreeNode* pRoot)
    // {
    //     if(pRoot==nullptr)
    //         return 0;
    //     TreeDepth_repeat(pRoot);
    //     return max_depth;
    // }

    int TreeDepth(TreeNode *pRoot)
    {
        //递归停止条件
        if (pRoot == nullptr)
            return 0;
        //父层是子层的深度加1
        int left = TreeDepth(pRoot->left);
        int right = TreeDepth(pRoot->right);
        return (left > right) ? (left + 1) : (right + 1);
    }
};