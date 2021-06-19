
//   Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 19. 删除链表的倒数第 N 个结点
// 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

// 进阶：你能尝试使用一趟扫描实现吗？

// 示例 1：
// 输入：head = [1,2,3,4,5], n = 2
// 输出：[1,2,3,5]

// 示例 2：
// 输入：head = [1], n = 1
// 输出：[]

// 示例 3：
// 输入：head = [1,2], n = 1
// 输出：[1]
 
// 提示：
// 链表中结点的数目为 sz
// 1 <= sz <= 30
// 0 <= Node.val <= 100
// 1 <= n <= sz

// -------------------第二次刷-----------------------
// 2021年6月8日15:55:01
// 准备第一次社招
// 思路: 蛮简单的, 删除链表必须记得加上辅助头节点以防删除的就是头节点. 要求只遍历一遍就弄个vector

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* new_head = new ListNode(0);
        new_head->next = head;

        vector<ListNode*> v;
        ListNode* p = new_head;
        while(p!=nullptr){
            v.push_back(p);
            p=p->next;
        }

        ListNode* target = v[v.size()-n];
        ListNode* left = v[v.size()-n-1];
        ListNode* right = target->next;
        left->next = right;

        return new_head->next;
    }
};