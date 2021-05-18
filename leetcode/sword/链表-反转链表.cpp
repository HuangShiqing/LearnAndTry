// 剑指 Offer 24. 反转链表
// 定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

// 示例:
// 输入: 1->2->3->4->5->NULL
// 输出: 5->4->3->2->1->NULL
 
// 限制：
// 0 <= 节点个数 <= 5000

// -------------------第三次刷-----------------------
// 2021年5月12日17:18:35
// 准备第一次社招
// 思路: 递归, 首先当找到最后一个有效节点时立马返回. 然后把当前节点的后续节点递归反转好, 然后反转当前节点. 

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
    ListNode* reverseList_repeat(ListNode* head) {
        // 找到最后的尾结点返回
        if(head->next==nullptr)
            return head;
        
        ListNode* r = reverseList_repeat(head->next);

        head->next->next = head;
        head ->next=nullptr;// 原本的第一个节点会需要, 其他的节点有没有这个都一样

        return r;
    }

    ListNode* reverseList(ListNode* head) {
        if(head==nullptr)
            return head;

        return reverseList_repeat(head);
    }
};


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

         