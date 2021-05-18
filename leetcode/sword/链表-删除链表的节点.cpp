// 剑指 Offer 18. 删除链表的节点
// 给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。
// 返回删除后的链表的头节点。
// 注意：此题对比原题有改动

// 示例 1:
// 输入: head = [4,5,1,9], val = 5
// 输出: [4,1,9]
// 解释: 给定你链表中值为 5 的第二个节点，那么在调用了你的函数之后，该链表应变为 4 -> 1 -> 9.

// 示例 2:
// 输入: head = [4,5,1,9], val = 1
// 输出: [4,5,9]
// 解释: 给定你链表中值为 1 的第三个节点，那么在调用了你的函数之后，该链表应变为 4 -> 5 -> 9.
 
// 说明：
// 题目保证链表中节点的值互不相同
// 若使用 C 或 C++ 语言，你不需要 free 或 delete 被删除的节点

// -------------------第三次刷-----------------------
// 2021年5月11日14:52:37
// 准备第一次社招
// 思路: 辅助节点+双指针就好了吧
// 注意事项: 链表的删除需要用到辅助节点以防止头节点就是需要删除的节点
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if(head == nullptr)
            return nullptr;

        ListNode* p0 = new ListNode(0);
        p0->next = head;

        ListNode* p1 = p0;
        ListNode* p2 = p0->next;

        while(p2->val!=val && p2!=nullptr){//访问->val的时候需要保证非空
            p1=p1->next;
            p2=p2->next;
        }
        p1->next = p2->next;//执行删除节点
        return p0->next;//辅助节点的后一个节点是真正的头结点
    }
};