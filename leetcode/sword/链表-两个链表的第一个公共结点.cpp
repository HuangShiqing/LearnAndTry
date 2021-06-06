// 剑指 Offer 52. 两个链表的第一个公共节点
// 输入两个链表，找出它们的第一个公共节点。

// 如下面的两个链表：
// 在节点 c1 开始相交。

// 示例 1：
// 输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3
// 输出：Reference of the node with value = 8
// 输入解释：相交节点的值为 8 （注意，如果两个列表相交则不能为 0）。从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,0,1,8,4,5]。在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。
 

// 示例 2：
// 输入：intersectVal = 2, listA = [0,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
// 输出：Reference of the node with value = 2
// 输入解释：相交节点的值为 2 （注意，如果两个列表相交则不能为 0）。从各自的表头开始算起，链表 A 为 [0,9,1,2,4]，链表 B 为 [3,2,4]。在 A 中，相交节点前有 3 个节点；在 B 中，相交节点前有 1 个节点。
 

// 示例 3：
// 输入：intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
// 输出：null
// 输入解释：从各自的表头开始算起，链表 A 为 [2,6,4]，链表 B 为 [1,5]。由于这两个链表不相交，所以 intersectVal 必须为 0，而 skipA 和 skipB 可以是任意值。
// 解释：这两个链表不相交，因此返回 null。
 
// 注意：
// 如果两个链表没有交点，返回 null.
// 在返回结果后，两个链表仍须保持原有的结构。
// 可假定整个链表结构中没有循环。
// 程序尽量满足 O(n) 时间复杂度，且仅用 O(1) 内存。
// 本题与主站 160 题相同：https://leetcode-cn.com/problems/intersection-of-two-linked-lists/


// -------------------第三次刷-----------------------
// 2021年5月31日14:48:44
// 准备第一次社招
// 思路: 很简单, 两个链表各遍历一遍获得长度差值, 然后长的先往前走差值个node, 然后长短一起往前并逐个比较是否相等, 相等则为第一个公共节点
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int length1=0;
        ListNode *p1 = headA;
        while(p1!=nullptr){
            p1 = p1->next;
            length1++;
        }
        int length2=0;
        ListNode *p2 = headB;
        while(p2!=nullptr){
            p2 = p2->next;
            length2++;
        }

        p1= headA;
        p2=headB;
        if(length1>length2){
            for(int i=0;i<length1-length2;i++)
                p1 = p1->next;
        }
        else if(length1<length2){
            for(int i=0;i<length2-length1;i++)
                p2 = p2->next;
        }

        while(p1!=p2 && p1!=nullptr && p2 != nullptr){
            p1=p1->next;
            p2=p2->next;
        }
        
        if(p1==nullptr || p2==nullptr)
            return nullptr;
        else
            return p1;
    }
};


//page:253
#include <iostream>
using namespace std;

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};
// class Solution {
// public:
//     int GetLength(ListNode* pHead1)
//     {
//         ListNode* pNode =pHead1;
//         int tlength =0;
//         while(pNode!=nullptr)
//         {
//             tlength++;
//             pNode= pNode->next;
//         }
//         return tlength;
//     }

//     ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        
//         int length1 = GetLength(pHead1);
//         int length2 = GetLength(pHead2);

//         ListNode* pLong;
//         ListNode* pShort;
//         int diff=0;
//         if(length1<=length2)
//         {
//             pShort = pHead1;
//             pLong = pHead2;
//             diff = length2-length1;
//         }
//         else
//         {
//             pShort = pHead2;
//             pLong = pHead1;
//             diff = length1-length2;
//         }

//         for(int i=0;i<diff;i++)
//         {
//             pLong = pLong->next;
//         }
//         while(pLong!=nullptr&&pShort!=nullptr&&pShort!=pLong)
//         {
//             pLong=pLong->next;
//             pShort=pShort->next;
//         }
//         return pLong;
//     }
// };



    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) 
    {
        if(pHead1==nullptr||pHead2==nullptr)
            return nullptr;
        int length1 = 0;
        int length2 = 0;
        ListNode* pNode=pHead1;
        while(pNode!=nullptr)
        {
            length1++;
            pNode = pNode->next;
        }

        pNode=pHead2;
        while(pNode!=nullptr)
        {
            length2++;
            pNode = pNode->next;
        }

        ListNode* pLong=nullptr;
        ListNode* pShort =nullptr;

        if(length1>=length2)
        {
            pLong=pHead1;
            pShort=pHead2;            
        }
        else
        {
            pLong=pHead2;
            pShort=pHead1;
        }        
        int diff = abs(length1-length2);
        
        while(diff!=0)
        {
            pLong=pLong->next;
            diff--;
        }

        while(pLong!=pShort&&pLong!=nullptr&&pShort!=nullptr)
        {
            pLong=pLong->next;
            pShort=pShort->next;
        }

        if(pLong==nullptr||pShort==nullptr)
            return nullptr;
        return pLong;
    }