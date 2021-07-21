// 92. 反转链表 II
// 给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。
 
// 示例 1：
// 输入：head = [1,2,3,4,5], left = 2, right = 4
// 输出：[1,4,3,2,5]

// 示例 2：
// 输入：head = [5], left = 1, right = 1
// 输出：[5]

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// -------------------第三次刷-----------------------
// 2021年7月19日17:36:59
// 准备第一次社招
// 思路: 用一个全局变量来控制当前node应该进行的操作. 
// left以左要做两个事, 一个就是不停往右递归走直到i=left-1, 另外一个就是当i=left-1时连上反转后的new_head.
// [left, right)就执行反转链表, 这里需要保留new_tail
// i=right时即相当于走到最后一个有意义的节点, 返回当前节点

class Solution {
public:
    int i=0;
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        i++;
        if(i<left){
            head->next = reverseBetween(head->next, left, right);
            return head;
        }
        else if(i>=left&&i<right){
            ListNode* new_head = reverseBetween(head->next, left, right);
            ListNode* new_tail = head->next->next;
            head->next->next = head;
            head->next = new_tail;
            return new_head;
        }
        else if(i==right){
            return head;
        }

        return nullptr;        
    }
};