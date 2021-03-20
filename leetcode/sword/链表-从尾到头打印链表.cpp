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