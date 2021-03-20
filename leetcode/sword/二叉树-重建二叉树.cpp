//page 62
#include <vector>
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

    TreeNode *reConstructBinaryTree_repeat(vector<int> pre, vector<int> vin,int pre_left,int pre_right,int in_left,int in_right)
    {
        TreeNode* root = new TreeNode(pre[pre_left]);
        //当只有一个值时，即该值作为最底层的root，不再递归
        if(pre_left==pre_right)
        {
            return root;
        }

        int root_index=in_left;
        while(vin[root_index]!=pre[pre_left])
            root_index++;
        
        int new_left_length=root_index-in_left;
        int new_right_length=in_right-root_index;

        if(new_left_length>0)
        {
            root->left=reConstructBinaryTree_repeat(pre,vin,pre_left+1,pre_left+new_left_length,in_left,root_index-1);
        }
        if(new_right_length>0)
        {
            root->right=reConstructBinaryTree_repeat(pre,vin,pre_left+1+new_left_length,pre_right,root_index+1,in_right);
        }
        return root;
    }

    TreeNode *reConstructBinaryTree(vector<int> pre, vector<int> vin)
    {
        if(pre.size()==0||vin.size()==0)
            return nullptr;
        
        return reConstructBinaryTree_repeat(pre,vin,0,pre.size()-1,0,vin.size()-1);
    }
};