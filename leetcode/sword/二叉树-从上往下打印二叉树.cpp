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