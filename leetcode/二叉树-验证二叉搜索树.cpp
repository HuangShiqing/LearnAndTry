#include <iostream>
#include <vector>
using namespace std;

// 98. 验证二叉搜索树
// 给定一个二叉树，判断其是否是一个有效的二叉搜索树。

// 假设一个二叉搜索树具有如下特征：

// 节点的左子树只包含小于当前节点的数。
// 节点的右子树只包含大于当前节点的数。
// 所有左子树和右子树自身必须也是二叉搜索树。

// 示例 1:
// 输入:
//     2
//    / \
//   1   3
// 输出: true

// 示例 2:
// 输入:
//     5
//    / \
//   1   4
//      / \
//     3   6
// 输出: false
// 解释: 输入为: [5,1,4,null,null,3,6]。
//      根节点的值为 5 ，但是其右子节点值为 4 。

// 二叉搜索树定义:
// 1.若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
// 2.若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
// 3.它的左右子树也为二叉搜索树
// 4.二叉搜索树「中序遍历」得到的值构成的序列一定是升序的

// -------------------第二次刷-----------------------
// 2021年6月17日10:37:26
// 准备第一次社招

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// 思路1: 最好理解. 中序遍历保存, 通过是否满足第4条来判断
class Solution {
public:
    void isValidBST(TreeNode* root, vector<int>& v){
        if(root == nullptr)
            return;
        isValidBST(root->left, v);
        v.push_back(root->val);
        isValidBST(root->right, v);
    }

    bool isValidBST(TreeNode* root) {
        vector<int> v;
        isValidBST(root, v);

        for(int i=0;i<v.size()-1;i++)
            if(v[i]>=v[i+1])
                return false;
        
        return true;
    }
};

// 思路2: 有点问题
// class Solution {
// public:
//     bool isValidBST(TreeNode* root, int min, int max) {
//         if(root == nullptr)
//             return true;
        
//         if(root->val>= max || root->val<= min)
//             return false;
        
//         return isValidBST(root->left, INT32_MIN, root->val) && isValidBST(root->right, root->val, INT32_MAX);
//     }

//     bool isValidBST(TreeNode* root) {
//         return isValidBST(root, INT32_MIN, INT32_MAX);
//     }
// };

// 思路3: 中序更新pre值. 稍微比较难理解为什么只保证root->val > pre, 没有保证root->val < after. 
class Solution {
public:
    long pre =LONG_MIN;//避免最左边的也是INT_MIN
    bool isValidBST(TreeNode* root) {
        if (root == nullptr)
            return true;

        //访问左子树
        if (!isValidBST(root->left))
            return false;
        //访问当前节点
        if (root->val <= pre)
            return false;
        pre = root->val;
        // 访问右子树
        return isValidBST(root->right);
    }
};