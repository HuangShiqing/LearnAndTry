// 148. 排序链表
// 给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

// 进阶：
// 你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？
 
// 示例 1：
// 输入：head = [4,2,1,3]
// 输出：[1,2,3,4]

// 示例 2：
// 输入：head = [-1,5,3,4,0]
// 输出：[-1,0,3,4,5]

// 示例 3：
// 输入：head = []
// 输出：[]

// -------------------第二次刷-----------------------
// 2021年06月19日09:57:28
// 准备第一次社招
// 思路: 就是归并排序的链表实现. 三步走
// 1. 用快慢指针找到中间node, 分成两个list
// 2. 递归排序两个list
// 3. 合并

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* find_middle(ListNode* head){
        if(head==nullptr||head->next==nullptr)
            return head;

        ListNode* slow = head;
        ListNode* fast = head->next->next;
        while(fast!=nullptr && fast->next!=nullptr){
            slow = slow ->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode* merge(ListNode* head1, ListNode* head2){
        ListNode* fake = new ListNode(-1);
        ListNode* node = fake;

        while(head1&&head2){
            if(head1->val<head2->val) {
                node->next = head1;
                head1 = head1->next;
            }
            else{
                node->next = head2;
                head2 = head2->next;
            }
            node = node->next;
        }

        node->next = head1?head1:head2;
        return fake->next;
    }

    ListNode* sortList(ListNode* head) {
        if(head==nullptr||head->next==nullptr)
            return head;
        
        ListNode* middle = find_middle(head);
        ListNode* right_head = middle->next;

        middle->next = nullptr;//注意这里要断开
        ListNode* head1 = sortList(head);
        ListNode* head2 = sortList(right_head);

        return merge(head1, head2);
    }
};

int main(){
    ListNode* node_4 = new ListNode(4);
    ListNode* node_2 = new ListNode(2);
    ListNode* node_1 = new ListNode(1);
    ListNode* node_3 = new ListNode(3);

    node_4->next = node_2;
    node_2->next = node_1;
    node_1->next = node_3;

    Solution s;
    s.sortList(node_4);
    return 1;

}