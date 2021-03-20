//page 194
#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <string>
#include <string.h>

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
    string g_s;
    void Serialize_repeat(TreeNode *root)
    {
        if (root)
        {
            g_s += to_string(root->val);
            g_s += ',';
            Serialize_repeat(root->left);
            Serialize_repeat(root->right);
        }
        else
        {
            g_s += '#';
            // g_s += ',';
        }
    }
    char *Serialize(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;
        Serialize_repeat(root);
        char *str = new char[g_s.size()]; //将整个string转成字符串
        strcpy(str, g_s.c_str());
        return str;
    }

    int g_index = 0;
    char *g_str = nullptr;
    void Deserialize_repeat(TreeNode **root)
    {
        if (*(g_str + g_index) == '\0')
            return;
        if (*(g_str + g_index) != '#')
        {
            int temp = *(g_str + g_index) - '0';
            g_index++;
            while (*(g_str + g_index) != ',')
            {
                temp = 10 * temp + *(g_str + g_index) - '0';
                g_index++;
            }
            TreeNode *left = new TreeNode(temp);
            (*root)->left = left;
            g_index += 1;
            Deserialize_repeat(&left);
        }
        else
        {
            (*root)->left = nullptr;
            g_index += 1;
        }

        if (*(g_str + g_index) != '#')
        {
            int temp = *(g_str + g_index) - '0';
            g_index++;
            while (*(g_str + g_index) != ',')
            {
                temp = 10 * temp + *(g_str + g_index) - '0';
                g_index++;
            }

            TreeNode *right = new TreeNode(temp);
            (*root)->right = right;
            g_index += 1;
            Deserialize_repeat(&right);
        }
        else
        {
            (*root)->right = nullptr;
            g_index += 1;
        }
    }

    TreeNode *Deserialize(char *str)
    {
        if (str == nullptr)
            return nullptr;
        g_str = str;

        int temp = *(g_str + g_index) - '0';
        g_index++;
        while (*(g_str + g_index) != ',')
        {
            temp = 10 * temp + *(g_str + g_index) - '0';
            g_index++;
        }
        g_index++;
        TreeNode *root = new TreeNode(temp);
        Deserialize_repeat(&root);
        return root;
    }
};

int main()
{

    // TreeNode *root = new TreeNode(8);
    // root->left = new TreeNode(6);
    // root->right = new TreeNode(10);

    // root->left->left = new TreeNode(5);
    // root->left->right = new TreeNode(7);

    // root->right->left = new TreeNode(9);
    // root->right->right = new TreeNode(11);

    // Solution solution;
    // char *s = new char[10];
    // s = solution.Serialize(root);

    Solution solution;
    char str[]="10,2,4,###3,5,##6,##";
    TreeNode *root = solution.Deserialize(str);

    return 0;
}
