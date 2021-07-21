#include <iostream>
#include <unordered_map>
using namespace std;

// 146. LRU 缓存机制
// 运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制 。
// 实现 LRUCache 类：
// LRUCache(int capacity) 以正整数作为容量 capacity 初始化 LRU 缓存
// int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
// void put(int key, int value) 如果关键字已经存在，则变更其数据值；如果关键字不存在，则插入该组「关键字-值」。当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。
 
// 进阶：你是否可以在 O(1) 时间复杂度内完成这两种操作？

// 示例：
// 输入
// ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
// [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
// 输出
// [null, null, null, 1, null, -1, null, -1, 3, 4]
// 解释
// LRUCache lRUCache = new LRUCache(2);
// lRUCache.put(1, 1); // 缓存是 {1=1}
// lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
// lRUCache.get(1);    // 返回 1
// lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
// lRUCache.get(2);    // 返回 -1 (未找到)
// lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
// lRUCache.get(1);    // 返回 -1 (未找到)
// lRUCache.get(3);    // 返回 3
// lRUCache.get(4);    // 返回 4

// -------------------第二次刷-----------------------
// 2021年06月19日09:57:28
// 准备第一次社招
// 思路: 
// 1. 一个hash map用来根据key查找val实现O(1)判断是否有key
// 2. 双向链表实现新旧顺序. 双向链表来表示新旧程度,最新使用的放在头,最老使用的放在尾,更新时只需要根据key找到对应的node断开前后
// 并移动到头即可,单链表无法恢复断开的前后. 只需要实现移动node和删除node
// 3. 双向链表的头尾加一个fake_head_node, fake_tail_node实现O(1)得到real_head_node, real_tail_node

struct LinkNode {
    int key;  //这个key是为了在移除最旧的时候能够移除链表里的node的同时根据key找到map里的对应项移除
    int val;
    LinkNode* pre;
    LinkNode* next;
    LinkNode(int k, int v) : key(k), val(v), pre(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map<int, LinkNode*> cache;
    int size;
    int capacity;
    //虚假的头尾节点可以实现O(1)时间找到最新使用和最旧使用的节点(真实的头尾节点)
    LinkNode* fake_head;
    LinkNode* fake_tail;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        size = 0;
        fake_head = new LinkNode(0, 0);
        fake_tail = new LinkNode(0, 0);
        fake_head->next = fake_tail;
        fake_tail->pre = fake_head;
    }

    int get(int key) {
        if (!cache.count(key))
            return -1;

        LinkNode* Node = cache[key];
        relink(Node);
        movetohead(Node);
        return Node->val;
    }

    void put(int key, int value) {
        if (!cache.count(key)) {  //不存在则添加并移动到头
            LinkNode* newNode = new LinkNode(key, value);
            cache[key] = newNode;
            movetohead(newNode);
            size++;
            if (size > capacity) {
                // remove real tail
                LinkNode* old_real_tail = fake_tail->pre;
                LinkNode* new_real_tail = old_real_tail->pre;
                fake_tail->pre = new_real_tail;
                new_real_tail->next = fake_tail;

                cache.erase(old_real_tail->key);
                delete old_real_tail;
                size--;
            }
        } else {  //存在则更新值并移动到头
            LinkNode* Node = cache[key];
            relink(Node);
            movetohead(Node);

            Node->val = value;
        }
    }

    void movetohead(LinkNode* Node) {
        LinkNode* old_real_head = fake_head->next;
        old_real_head->pre = Node;
        Node->next = old_real_head;
        fake_head->next = Node;
        Node->pre = fake_head;
    }

    void relink(LinkNode* Node) {
        LinkNode* pre_Node = Node->pre;
        LinkNode* next_Node = Node->next;

        pre_Node->next = next_Node;
        next_Node->pre = pre_Node;
    }
};

int main(int argc, char const *argv[])
{
    auto cache = LRUCache(2);
    cache.put(1,1);
    cache.put(2,2);
    int a = cache.get(1);
    cache.put(3,3);
    a = cache.get(2);
    cache.put(4,4);
    a = cache.get(1);
    a = cache.get(3);
    a = cache.get(4);
    return 0;
}
