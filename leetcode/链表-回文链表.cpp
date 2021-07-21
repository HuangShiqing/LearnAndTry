#include <iostream>
#include <vector>
using namespace std;

// 234. 回文链表
// 请判断一个链表是否为回文链表。

// 示例 1:
// 输入: 1->2
// 输出: false

// 示例 2:
// 输入: 1->2->2->1
// 输出: true
// 进阶：
// 你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？

// -------------------第二次刷-----------------------
// 2021年6月28日11:24:58
// 准备第一次社招
// 思路: 找到中间节点, 反转后面, 然后一一比较
// 快慢指针
// 总数为奇数:当不满足fast&&fast->next时,slow指向中间
// 总数为奇数:当不满足fast&&fast->next时,slow指向中间靠后
// 不重要,只要从slow开始的后半段反转一下,然后比较即可

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *ReverseList_2(ListNode *pHead)
    {
        // 第一个==是针对第一次调用的输入直接是nullptr
        // 第二个==是针对最后找到尾结点时返回尾结点
        if (pHead == nullptr || pHead->next == nullptr)
            return pHead;
        // 因为反转之后访问不到下一个节点，即返回回来新链表的尾结点，所以先保存下一个节点
        ListNode* temp = pHead->next;//保存下一个节点
        ListNode* newHead = ReverseList_2(pHead->next);//整体思维，宏观语义
        // 新链表的尾结点的next指向当前节点
        temp->next = pHead;//连上头与递归部分
        // 当前节点成了新链表的尾结点，把该节点指向nullptr
        pHead->next = nullptr;//调整尾部
        return newHead;//返回头节点
    }

    bool isPalindrome(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast&&fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* newhalfhead = ReverseList_2(slow);
        while(newhalfhead&&head){
            if(newhalfhead->val!=head->val)
                return false;
            newhalfhead=newhalfhead->next;
            head=head->next;
        }
        return true;
    }
};