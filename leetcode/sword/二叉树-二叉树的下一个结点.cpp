//page 65
#include <iostream>

using namespace std;

struct TreeLinkNode
{
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL)
    {
    }
};

class Solution
{
public:
    // TreeLinkNode *GetNext(TreeLinkNode *pNode)
    // {
    //     if (pNode == nullptr)
    //         return nullptr;

    //     TreeLinkNode *pnext = nullptr;
    //     if (pNode->right != nullptr)
    //     {
    //         TreeLinkNode *pright = pNode->right;
    //         while (pright->left != nullptr)
    //             pright = pright->left;
    //         pnext = pright;
    //     }
    //     else if (pNode->next != nullptr)
    //     {
    //         TreeLinkNode *pcurrent = pNode;
    //         TreeLinkNode *pparent = pNode->next;
    //         if(pparent !=nullptr&&pcurrent==pparent->left)
    //         {
    //             pnext=pparent;
    //         }
    //         else if (pparent !=nullptr&&pcurrent==pparent->right)
    //         {
    //             while (pparent !=nullptr&&pcurrent==pparent->right)
    //             {
    //                 pcurrent=pparent;
    //                 pparent=pparent->next;
    //             }
    //             pnext=pparent;
    //         }

    //     }

    //     return pnext;
    // }
    TreeLinkNode *GetNext(TreeLinkNode *pNode)
    {
        if (pNode == nullptr)
            return nullptr;

        //分两种情况，是否有右子节点，有的话下一节点肯定在右子节点中，否则肯定在父节点中
        if (pNode->right)
        {
            pNode = pNode->right;
            while (pNode->left)
            {
                pNode = pNode->left;
            }
            return pNode;
        }
        //否则肯定在父节点中
        else
        {
            TreeLinkNode *pParent = pNode->next;
            if (pParent == nullptr)
                return nullptr;
            //如果该节点是父节点的右子节点，下一节点就是父节点
            if (pNode == pParent->left)
                return pParent;
            //否则
            else if (pNode == pParent->right)
            {
                do
                {
                    if (pParent->next == nullptr)
                        return nullptr;
                    pNode = pParent;
                    pParent = pNode->next;
                } while (pNode == pParent->right);
                return pParent;
            }
        }
    }
};