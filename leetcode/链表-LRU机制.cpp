#include <iostream>
#include <unordered_map>
using namespace std;

//一个hash map用来根据key查找val
// 双向链表来表示新旧程度,最新使用的放在头,最老使用的放在尾,更新时只需要根据key找到对应的node断开前后
// 并移动到头即可,单链表无法恢复断开的前后

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
        movetohead(Node);
        relink(Node);
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
            movetohead(Node);
            relink(Node);

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
