//page 187
#include <iostream>
using namespace std;

struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};

class Solution {
public:
    // RandomListNode* Clone(RandomListNode* pHead)
    // {
    //     if (!pHead) return NULL;
    // nodeClone(pHead);
    // connectRandom(pHead);
    // return reconnect(pHead);
    // }
     
     
// //[1]复制结点，插入到原结点后方
// void nodeClone(RandomListNode *pHead)
// {
//     RandomListNode* pNode = pHead;
//     while(pNode != nullptr)
//     {
//         RandomListNode *pnew = new RandomListNode(pNode->label);
//         pnew ->next = pNode->next;
//         //pnew ->label = pNode->label;
//         //pnew ->random = nullptr;
//         pNode->next = pnew;

//         pNode = pnew->next;
//     }
// }
 
// //[2]还原新结点的random指针
// void connectRandom(RandomListNode *pHead)
// {
//     RandomListNode* pNode = pHead;
//     while(pNode != nullptr)
//     {
//         RandomListNode* pClone = pNode->next;
//         if(pNode->random)
//             pClone->random = pNode->random->next;
//         pNode = pClone->next;
//     }
    
// }
 
// //[3]拆分
// RandomListNode *reconnect(RandomListNode *pHead)
// {
//     RandomListNode* pNode = pHead;        
//     RandomListNode *presult = pHead->next;

//     while(pNode!=nullptr)
//     {
//         RandomListNode* pClone = pNode->next;
//         pNode->next = pClone->next;
//         pNode = pNode->next;
//         if(pNode != nullptr)
//             pClone ->next = pNode ->next;
//     }
//     return presult;
// }
    
    RandomListNode* Clone(RandomListNode* pHead)
    {
        if(pHead==nullptr)
            return nullptr;
        if(pHead->next==nullptr)
            return nullptr;


        CloneNode(pHead);
        SetRandomNode(pHead);
        return SplitNode( pHead);
    }

    void CloneNode(RandomListNode* pHead)
    {
        RandomListNode* pNext=nullptr;
        while(pHead!=nullptr)
        {
            RandomListNode* pNew = new RandomListNode(pHead->label);
            pNext = pHead->next;
            pHead->next=pNew;
            pNew->next=pNext;

            pHead=pNext;
        }
    }

    void SetRandomNode(RandomListNode* pHead)
    {
        RandomListNode* pOld=pHead;
        RandomListNode* pNew=pHead->next;

        while(1)
        {
            //p->random 可能等于nullptr
            if(pOld->random)
                pNew->random = pOld->random->next;

            pOld=pNew->next;
            if(pOld==nullptr)
                break;
            pNew=pOld->next;
        }
    }

    RandomListNode* SplitNode(RandomListNode* pHead)
    {
        RandomListNode* pOld=pHead;
        RandomListNode* pNew=pHead->next;
        RandomListNode* pNewHead = pNew;

        while(1)
        {
            pOld->next=pNew->next;
            pOld=pOld->next;
            if(pOld==nullptr)
                break;

            pNew->next=pOld->next;
            pNew=pNew->next;
        }
        pNew->next=nullptr;

        return pNewHead;
    }
};


int main()
{

}