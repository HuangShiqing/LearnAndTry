#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// 617. 合并二叉树
// 给定两个二叉树，想象当你将它们中的一个覆盖到另一个上时，两个二叉树的一些节点便会重叠。
// 你需要将他们合并为一个新的二叉树。合并的规则是如果两个节点重叠，那么将他们的值相加作为节点合并后的新值，
// 否则不为 NULL 的节点将直接作为新二叉树的节点。
// 示例 1:
// 输入: 
// 	Tree 1                     Tree 2                  
//           1                         2                             
//          / \                       / \                            
//         3   2                     1   3                        
//        /                           \   \                      
//       5                             4   7                  
// 输出: 
// 合并后的树:
// 	     3
// 	    / \
// 	   4   5
// 	  / \   \ 
// 	 5   4   7
// 注意: 合并必须从两个树的根节点开始。

// -------------------第二次刷-----------------------
// 2021年7月20日10:53:04
// 准备第一次社招
// 思路: 递归即可. 具体流程看代码

class Solution {
public:    
    // TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    //     if (root1 == nullptr && root2 == nullptr)
    //         return nullptr;

    //     TreeNode* merged = new TreeNode();
    //     // merged->val = root1 ? root1->val : 0 + root2 ? root2->val : 0;

    //     mergeTrees_repeat(root1, root2, merged);
    //     return merged;
    // }

    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        //如果有一个为nullptr,那都不用新建了,直接返回另外一个连上即可
        if (root1 == nullptr) {
            return root2;
        }
        if (root2 == nullptr) {
            return root1;
        }
        auto merged = new TreeNode(root1->val + root2->val);
        merged->left = mergeTrees(root1->left, root2->left);
        merged->right = mergeTrees(root1->right, root2->right);
        return merged;
    }
};