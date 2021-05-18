//page 58

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct ListNode
{
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL)
    {
    }
};

// vector<int> printListFromTailToHead(ListNode *head)
// {
//     if (head != nullptr)
//     {
//         if (head->next!=nullptr)
//         {
//             printListFromTailToHead(head->next);
//         }
//         return head->val;
//     }
// }

// vector<int> printListFromTailToHead(ListNode *head)
// {
//     vector<int> v;
//     stack<ListNode *> s;
//     if(head==nullptr)
//         return v;
    
//     while(head!=nullptr)
//     {
//         s.push(head);
//         head=head->next;
//     }

//     while(s.size())
//     {
//         v.push_back(s.top()->val);
//         s.pop();
//     }

//     return v;
// }
vector<int> v;

void printListFromTailToHead_repeat(ListNode *head)
{
    if(head==nullptr)
        return;
    printListFromTailToHead_repeat(head->next);
    v.push_back(head->val);
}

vector<int> printListFromTailToHead(ListNode *head)
{
    if(head==nullptr)
        return v;
    printListFromTailToHead_repeat(head);
    return v;
}

// 剑指 Offer 06. 从尾到头打印链表
// 输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。
// 示例 1：
// 输入：head = [1,3,2]
// 输出：[2,3,1]

// 2021年04月24日15:22:50
// 准备第一次社招
// 思路:
// 后序遍历, 很简单, 不多说

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> v;
    void reversePrint_repeat(ListNode* head){
        if(head==nullptr)
            return;
        reversePrint_repeat(head->next);
        v.push_back(head->val);
    }
    vector<int> reversePrint(ListNode* head) {
        if(head==nullptr)
            return v;
        reversePrint_repeat(head);
        return v;
    }
};