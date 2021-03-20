//page:142
#include <iostream>

struct ListNode
{
    int val;
    struct ListNode *next;
    // ListNode(int x) : val(x), next(NULL)
    // {
    // }
};
// class Solution {
// public:
//     ListNode* ReverseList(ListNode* pHead) {
//         ListNode *pNode = pHead;
//         ListNode *pPre = nullptr;
//         ListNode *pReverse = nullptr;
//         while(pNode!=nullptr)
//         {
//             ListNode *pNext = pNode->next;
//             if(pNext==nullptr)
//                 pReverse = pNode;
//             pNode->next = pPre;
//             pPre = pNode;
//             pNode = pNext;
//         }
//         return pReverse;
//     }
// };

class Solution
{
public:
    // ListNode* ReverseList(ListNode* pHead)
    // {
    //     if(pHead==nullptr)
    //         return nullptr;

    //     if(pHead->next==nullptr)
    //         return pHead;

    //     ListNode* pNode=pHead->next;
    //     pHead->next=nullptr;
    //     ListNode* pPre=pHead;
    //     ListNode* pNext =nullptr;
    //     while(pNode!=nullptr)
    //     {
    //         pNext=pNode->next;
    //         pNode->next=pPre;

    //         pPre = pNode;
    //         pNode=pNext;
    //     }
    //     return pPre;
    // }

    ListNode *ReverseList(ListNode *pHead)
    {
        if (pHead == nullptr || pHead->next == nullptr)
            return pHead;
        ListNode *pReturn = nullptr;

    //三个指针，前中后
    ListNode *pNode = pHead;
    ListNode *pPre = nullptr;
    ListNode *pNext = nullptr;
    while (1)
    {
        //每次操作就是更新后指针以及反转指向
        pNext = pNode->next;
        pNode->next = pPre;
        //停止
        if (pNext == nullptr)
        {
            pReturn = pNode;
            return pReturn;
        }
        //更新操作为更新前中
        pPre = pNode;
        pNode = pNext;
    }
}

// 递归
// 最终是要获得新链表的头结点，即原始链表的尾结点（nullptr前面那个节点），
// 所以递归操作输入是下一个链表节点，返回值是递归函数的返回值或者当找到尾结点时直接返回
ListNode *ReverseList_2(ListNode *pHead)
{
    // 第一个==是针对第一次调用的输入直接是nullptr
    // 第二个==是针对最后找到尾结点时返回尾结点
    if (pHead == nullptr || pHead->next == nullptr)
        return pHead;
    // 因为反转之后访问不到下一个节点，即返回回来新链表的尾结点，所以先保存下一个节点
    ListNode* temp = pHead->next;//保存下一个节点
    ListNode* newHead = ReverseList_2(pHead->next);//整体思维，宏观语义
    // 新链表的尾结点的next指向当前节点
    temp->next = pHead;//连上头与递归部分
    // 当前节点成了新链表的尾结点，把该节点指向nullptr
    pHead->next = nullptr;//调整尾部
    return newHead;//返回头节点
}

         