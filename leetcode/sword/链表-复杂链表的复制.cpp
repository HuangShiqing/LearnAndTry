// 剑指 Offer 35. 复杂链表的复制
// 请实现 copyRandomList 函数，复制一个复杂链表。在复杂链表中，
// 每个节点除了有一个 next 指针指向下一个节点，还有一个 random 指针指向链表中的任意节点或者 null。

// 示例 1：
// 输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
// 输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]

// 示例 2：
// 输入：head = [[1,1],[2,1]]
// 输出：[[1,1],[2,1]]

// 示例 3：
// 输入：head = [[3,null],[3,0],[3,null]]
// 输出：[[3,null],[3,0],[3,null]]

// 示例 4：
// 输入：head = []
// 输出：[]
// 解释：给定的链表为空（空指针），因此返回 null。

// 2021年05月15日22:37:21
// 准备第一次社招
// 思路: 即使是常规链表, 直接复制的也会造成新node->next指向原node->next, 更何况这个复杂链表
// 流程分三步
// 第一步复制:在每个原node后面插入该node的复制. 
// 第二步重连:把复制出来的node->random变成node->random->next. 
// 第三步分离:把新node和原node分开

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    void copy(Node* head){
        if(head==nullptr)
            return;
        
        Node* old_next = head->next;
        Node* new_next = new Node(head->val);
        head->next = new_next;
        new_next->next = old_next;

        copy(old_next);
    }

    void reset(Node* head){
        if(head==nullptr)
            return;
        
        // head->node_2->node_3->node_4
        Node* node_2 = head->next;
        // old random可能指向nullptr
        if(head->random)
            node_2->random = head->random->next;
        else
            node_2->random = nullptr;

        Node* node_3 = head->next->next;
        reset(node_3);
    }

    Node* split(Node* head){
        if(head==nullptr)
            return nullptr;
        // head->node_2->node_3->node_4
        Node* node_2 = head->next;
        Node* node_3 = head->next->next;
        Node* node_4 = split(node_3);
        node_2->next = node_4;
        head->next = node_3;

        return node_2;
    }

    Node* copyRandomList(Node* head) {
        copy(head);
        reset(head);
        return split(head);
    }
};

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