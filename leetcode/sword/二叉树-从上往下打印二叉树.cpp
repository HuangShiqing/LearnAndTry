// 剑指 Offer 32 - I. 从上到下打印二叉树
// 从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。

// 例如:
// 给定二叉树: [3,9,20,null,null,15,7],
//     3
//    / \
//   9  20
//     /  \
//    15   7
// 返回：
// [3,9,20,15,7]

// -------------------第三次刷-----------------------
// 2021年5月13日19:53:10
// 准备第一次社招
// 思路: 用一个前后都可以进出的队列即可. 每次递归都从deque里取出front node, 处理内容为把node->val保存, 
// 然后把node->left和node->right先后push_back到deque里. 最后再执行一次递归函数. 递归结束的条件是deque为空

#include <deque>
using namespace std;
#include <vector>
struct TreeNode
{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};

class Solution {
public:
	void levelOrder_repeat(deque<TreeNode*>& d, vector<int>& v){
		if(d.size()==0)
			return;

		TreeNode* root = d.front();
		d.pop_front();
		v.push_back(root->val);

		if(root->left)
			d.push_back(root->left);
		if(root->right)
			d.push_back(root->right);
		levelOrder(d, v);
	}

    vector<int> levelOrder(TreeNode* root) {
		vector<int> v;
		deque<TreeNode*> d;
		if(root==nullptr)
			return v;

		d.push_back(root);
		levelOrder_repeat(d, v);

		return v;
    }
};


#include <iostream>
#include <vector>
#include <deque>
using namespace std;

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
	// vector<int> v;

public:
	// vector<int> PrintFromTopToBottom(TreeNode *root)
	// {
	// 	if (root == nullptr)
	// 		return v;
	// 	deque<TreeNode *> dqTreeNode;
	// 	dqTreeNode.push_back(root);

	// 	while (dqTreeNode.size())
	// 	{
	// 		TreeNode *p = dqTreeNode.front();
	// 		dqTreeNode.pop_front();
	// 		v.push_back(p->val);

	// 		if(p->left)
	// 			dqTreeNode.push_back(p->left);
	// 		if(p->right)
	// 			dqTreeNode.push_back(p->right);
	// 	}

	// 	return v;
	// }

	vector<int> PrintFromTopToBottom(TreeNode *root)
	{
		//队列保存节点，每次访问头位置的节点，将头节点的值放到v中，然后把头节点的子节点加入到队列的队尾
		vector<int> v;
		deque<TreeNode *> q;
		if (root == nullptr)
			return v;
		q.push_back(root);
		v.push_back(root->val);
		TreeNode *node = nullptr;
		while (q.size())
		{
			node = q.front();
			if (node->left)
			{
				q.push_back(node->left);
				v.push_back(node->left->val);
			}
			if (node->right)
			{
				q.push_back(node->right);
				v.push_back(node->right->val);
			}
			q.pop_front();
		}
		return v;
	}
};

int main()
{

	TreeNode *ptree_root = new TreeNode;
	ptree_root->val = 8;
	ptree_root->left = new TreeNode;
	ptree_root->left->val = 6;
	ptree_root->right = new TreeNode;
	ptree_root->right->val = 10;
	ptree_root->left->left = new TreeNode;
	ptree_root->left->left->val = 5;
	ptree_root->left->right = new TreeNode;
	ptree_root->left->right->val = 7;
	ptree_root->right->left = new TreeNode;
	ptree_root->right->left->val = 9;
	ptree_root->right->right = new TreeNode;
	ptree_root->right->right->val = 11;

	Solution solution;
	vector<int> a = solution.PrintFromTopToBottom(ptree_root);
}