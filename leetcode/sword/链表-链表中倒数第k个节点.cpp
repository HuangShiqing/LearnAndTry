// 剑指 Offer 22. 链表中倒数第k个节点
// 输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。

// 例如，一个链表有 6 个节点，从头节点开始，它们的值依次是 1、2、3、4、5、6。这个链表的倒数第 3 个节点是值为 4 的节点。

// 示例：
// 给定一个链表: 1->2->3->4->5, 和 k = 2.
// 返回链表 4->5.

// -------------------第三次刷-----------------------
// 2021年5月12日11:38:45
// 准备第一次社招
// 思路: 前后指针, 很简单
// 注意: 在一开始移动p2的时候不需要每次更改指针后都需要判断是否到nullptr, 因为预设了k值在合理范围内. 如果加了的话,在求链表[1]倒数第1个节点会出错

struct ListNode{
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL){}
};

class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* p1 = head;
        ListNode* p2 = head;
        while(k!=0){
            p2=p2->next;
            k--;
            // if(p2==nullptr)// 不需要
            //     return nullptr;
        }
            
        while(p2 != nullptr){
            p1 = p1->next;
            p2 = p2->next;
        }
        return p1;
    }
};

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