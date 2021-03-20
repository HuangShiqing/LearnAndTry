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