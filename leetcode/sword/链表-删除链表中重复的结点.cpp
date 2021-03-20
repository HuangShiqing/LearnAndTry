//page 122
#include <iostream>
// #include <unordered_map>
// #include <string>
using namespace std;

struct ListNode
{
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL)
    {
    }
};

class Solution
{
public:    
    ListNode *deleteDuplication(ListNode *pHead)
    {
        if (pHead == nullptr || pHead->next == nullptr)
            return pHead;

        //新建一个辅助节点来处理头节点也是重复节点的情况
        ListNode *pNew = new ListNode(0);
        pNew->next = pHead;
        pHead = pNew;

        ListNode *pFront = pHead;
        ListNode *pNode = pHead->next;

        while (pNode != nullptr)
        {
            if (pNode->next != nullptr && pNode->val == pNode->next->val)
            {
                while (pNode->next != nullptr && pNode->val == pNode->next->val)
                {
                    pNode = pNode->next;
                }
                if (pNode->next == nullptr)
                {
                    pFront->next = nullptr;
                    return pHead->next;
                }
                else if (pNode->val != pNode->next->val)
                {
                    pFront->next = pNode->next;
                    pNode = pNode->next;
                }
            }
            else
            {
                pFront = pNode;
                pNode = pNode->next;
            }
        }
        return pHead->next;
    }
};

    // 递归
    ListNode* deleteDuplication_2(ListNode* pHead)
    {
        if (pHead == nullptr || pHead->next == nullptr)        
            return pHead;
        
        if (pHead->val == pHead->next->val)
        {
            ListNode* node = pHead->next; //当前开始重复的节点用pHead标记
            while (node != nullptr && node->val == pHead->val)            
                node = node->next;
            
            //循环出来以后node指向下一个不重复的点，下一步从这个节点开始继续查找重复的节点
            return deleteDuplication_2(node);
        }
        else
        {
            //如果这个节点和下一个节点不重复，则继续从下一个节点开始找重复的
            pHead->next = deleteDuplication_2(pHead->next);
            return pHead;
        }
    }
};