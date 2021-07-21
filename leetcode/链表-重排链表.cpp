// 给定一个单链表 L 的头节点 head ，单链表 L 表示为：
//  L0 → L1 → … → Ln-1 → Ln 
// 请将其重新排列后变为：
// L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …
// 不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
//  
// 示例 1:
// 输入: head = [1,2,3,4]
// 输出: [1,4,2,3]

// 示例 2:
// 输入: head = [1,2,3,4,5]
// 输出: [1,5,2,4,3]

// -------------------第二次刷-----------------------
// 2021年07月19日19:13:58
// 准备第一次社招
// 思路:
// 注意到目标链表即为将原链表的左半端和反转后的右半端合并后的结果。
// 这样我们的任务即可划分为三步：
// 1. 找到原链表的中点（参考「876. 链表的中间结点」）。我们可以使用快慢指针来 O(N)地找到链表的中间节点。
// 2. 将原链表的右半端反转（参考「206. 反转链表」）。我们可以使用迭代法实现链表的反转。
// 3. 将原链表的两端合并。因为两链表长度相差不超过 11，因此直接合并即可。

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode* reverseList(ListNode* head) {
        if(head==nullptr)
            return head;
        if(head->next==nullptr)
            return head;
        
        ListNode* new_head = reverseList(head->next);
        ListNode* new_tail = head->next->next;
        head->next->next = head;
        head->next = new_tail;

        return new_head;
    }

    void mergeList(ListNode* l1, ListNode* l2) {
        ListNode* l1_tmp;
        ListNode* l2_tmp;
        while (l1 != nullptr && l2 != nullptr) {
            l1_tmp = l1->next;
            l2_tmp = l2->next;

            l1->next = l2;
            l1 = l1_tmp;

            l2->next = l1;
            l2 = l2_tmp;
        }
    }

    void reorderList(ListNode* head) {
        if (head == nullptr) {
            return;
        }
        ListNode* mid = middleNode(head);
        ListNode* l1 = head;
        ListNode* l2 = mid->next;
        mid->next = nullptr;
        l2 = reverseList(l2);
        mergeList(l1, l2);
    }
};