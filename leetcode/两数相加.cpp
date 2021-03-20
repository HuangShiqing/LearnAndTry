#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

// 给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。
// 如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
// 您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
// 示例：
// 输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
// 输出：7 -> 0 -> 8
// 原因：342 + 465 = 807
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };
 
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int add = 0;
        ListNode* phead = new ListNode(((l1->val+l2->val+add)%10));;
        add = (l1->val+l2->val+add)/10;
        l1 = l1->next;
        l2 = l2->next;

        ListNode* l3 = phead;
        while(l1!=NULL&&l2!=NULL)
        {
            l3->next = new ListNode(((l1->val+l2->val+add)%10));
            add = (l1->val+l2->val+add)/10;
            l1 = l1->next;
            l2 = l2->next;
            l3 = l3 ->next;
        }
        while(l1!=NULL)
        {
            l3->next = new ListNode((l1->val+add)%10);
            add = (l1->val+add)/10;
            l1 = l1->next;
            l3 = l3->next;
        }
        while(l2!=NULL)
        {
            l3->next = new ListNode((l2->val+add)%10);
            add = (l2->val+add)/10;
            l2 = l2->next;
            l3 = l3->next;
        }
        if(add)
        {
            l3->next = new ListNode(add%10);
            add = add/10;
        }
            
        return phead;


        
    }
};