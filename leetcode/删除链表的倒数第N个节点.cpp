
//   Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* left = head;
        ListNode* middle = head;
        ListNode* right = head;
        while(n-1>0&&right->next != nullptr){
            right = right->next;
            n--;
        }
        if(right->next != nullptr)
        {
            middle = middle->next;
            right = right->next;
        }
        while(right->next != nullptr)
        {
            left = left->next;
            middle = middle->next;
            right = right->next;
        }

        left->next = middle->next;
        // TODO:
        return head;
    }
};