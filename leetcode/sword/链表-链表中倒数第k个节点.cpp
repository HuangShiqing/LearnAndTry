//page:134
#include <iostream>

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
    // ListNode *FindKthToTail(ListNode *pListHead, unsigned int k)
    // {
    //     if (pListHead == nullptr || k == 0)
    //         return nullptr;

    //     ListNode *phead = pListHead;
    //     ListNode *pbehind = nullptr;

    //     for (int i = 0; i < k - 1; i++)
    //     {
    //         if (phead->next != nullptr)
    //             phead = phead->next;
    //         else
    //             return nullptr;
    //     }

    //     pbehind = pListHead;
    //     while (phead->next != nullptr)
    //     {
    //         phead = phead->next;
    //         pbehind = pbehind->next;
    //     }
    //     return pbehind;
    // }

    ListNode *FindKthToTail(ListNode *pListHead, unsigned int k)
    {
        if(pListHead==nullptr)
            return nullptr;
        ListNode* pfront=pListHead;
        ListNode* pbehind=pListHead;
        for(int i=0;i<k-1;i++)
        {
            pfront = pfront->next;
            if(pfront==nullptr)
                return nullptr;
        }

        while(pfront->next!=nullptr)
        {
            pfront=pfront->next;
            pbehind=pbehind->next;
        }
        return pbehind;

    }
};