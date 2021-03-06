// 剑指 Offer 25. 合并两个排序的链表
// 输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。

// 示例1：

// 输入：1->2->4, 1->3->4
// 输出：1->1->2->3->4->4
// 限制：

// 0 <= 链表长度 <= 1000

// -------------------第三次刷-----------------------
// 2021年5月12日19:25:33
// 准备第一次社招
// 思路: 递归, 应该蛮简单的. 比以前的写法优雅多了
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode* mergeTwoLists_repeat(ListNode* l1, ListNode* l2){
        if(l1==nullptr&&l2==nullptr)
            return nullptr;
        else if(l1==nullptr&&l2!=nullptr)
            return l2;
        else if(l1!=nullptr&&l2==nullptr)
            return l1;

        if(l1->val < l2->val){
            l1->next = mergeTwoLists_repeat(l1->next, l2);
            return l1;
        }
        else{
            l2->next = mergeTwoLists_repeat(l1, l2->next);
            return l2;
        }

    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        return mergeTwoLists_repeat(l1, l2);
    }
};


//page:145
#include <iostream>
#include "LinkList.hpp"
using namespace std;

// struct ListNode
// {
//     int val;
//     struct ListNode *next;
//     // ListNode(int x) :
//     // 		val(x), next(NULL) {
//     // }
// };

// class Solution
// {
// public:
//     ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
//     {
//         if (pHead1 == nullptr)
//             return pHead2;
//         else if (pHead2 == nullptr)
//             return pHead1;

//         ListNode *pMergedHead = nullptr;

//         if (pHead1->val < pHead2->val)
//         {
//             pMergedHead = pHead1;
//             pMergedHead->next = Merge(pHead1->next, pHead2);
//         }
//         else
//         {
//             pMergedHead = pHead2;
//             pMergedHead->next = Merge(pHead1, pHead2->next);
//         }
//         return pMergedHead;
//     }

//     ListNode *Merge2(ListNode *pHead1, ListNode *pHead2)
//     {
//         ListNode *pMergedHead = nullptr;

//         if(pHead1==nullptr&&pHead2!=nullptr)
//             return pHead2;
//         else if(pHead2==nullptr&&pHead1!=nullptr)
//             return pHead1;
//         else if(pHead1==nullptr&&pHead2==nullptr)
//             return nullptr;

//         if (pHead1->val < pHead2->val)
//         {
//             pMergedHead = pHead1;
//             pHead1 = pHead1->next;
//         }
//         else
//         {
//             pMergedHead = pHead2;
//             pHead2 = pHead2->next;
//         }
//         ListNode *pMergedHead_temp = pMergedHead;


//         while (1)
//         {
//             if (pHead1 == nullptr)
//             {
//                 pMergedHead->next = pHead2;
//                 return pMergedHead_temp;
//             }
//             else if (pHead2 == nullptr)
//             {
//                 pMergedHead->next = pHead1;
//                 return pMergedHead_temp;
//             }

//             if (pHead1->val < pHead2->val)
//             {
//                 pMergedHead->next = pHead1;
//                 pHead1 = pHead1->next;
//             }
//             else
//             {
//                 pMergedHead->next = pHead2;
//                 pHead2 = pHead2->next;
//             }
//             pMergedHead = pMergedHead->next;
//         }
//     }
// };
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        if(pHead1==nullptr)
            return pHead2;
        if(pHead2==nullptr)
            return pHead1;
        
        ListNode* pMerge=nullptr;
        if(pHead1->val<pHead2->val)
        {
            pMerge=pHead1;
            pHead1=pHead1->next;
        }
        else
        {
            pMerge=pHead2;
            pHead2=pHead2->next;
        }
        ListNode* pReturn =pMerge;


        while(pHead1!=nullptr&&pHead2!=nullptr)
        {
            if(pHead1->val<pHead2->val)
            {
                pMerge->next=pHead1;
                pMerge=pMerge->next;
                pHead1=pHead1->next;
            }
            else
            {
                pMerge->next=pHead2;
                pMerge=pMerge->next;
                pHead2=pHead2->next;
            }            
        }

        if(pHead1==nullptr&&pHead2!=nullptr)
        {
            pMerge->next=pHead2;
        }
        else if(pHead2==nullptr&&pHead1!=nullptr)
        {
            pMerge->next=pHead1;
        }
        else if(pHead2==nullptr&&pHead1==nullptr)
            ;
        return pReturn;

    }
};


// int main()
// {
//     int num1[3] = {1,3,5};
//     int num2[3] = {2,4,6};
//     ListNode * pHead1 = LinkList_init(num1, 3);
//     ListNode * pHead2 = LinkList_init(num2, 3);

//     Solution solution;  
//     solution.Merge2(pHead1,pHead2);
// }