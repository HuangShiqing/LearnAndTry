
//page:139
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

struct ListNode
{
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL)
    {
    }
};

// class Solution
// {
// public:
//     unordered_map<ListNode *, int> map;

//     ListNode *EntryNodeOfLoop(ListNode *pHead)
//     {
//         if (pHead == nullptr)
//             return pHead;

//         while (pHead != nullptr)
//         {
//             if (map.find(pHead) == map.end())
//             {
//                 map[pHead] = 1;
//             }
//             else
//             {
//                 return pHead;
//             }

//             pHead = pHead->next;
//         }
//         return nullptr;
//     }
// };
// class Solution {
// public:
//     ListNode* MeetingNode(ListNode* pHead)
//     {
//         if(pHead==nullptr)
//             return nullptr;
//         ListNode* pslow = pHead->next;
//         if(pslow==nullptr)
//             return nullptr;
//         ListNode* pfast = pslow->next;
//         if(pfast==nullptr)
//             return nullptr;

//         while(pfast!=nullptr&&pslow!=nullptr)
//         {
//             if(pfast==pslow)
//                 return pslow;
//             pslow=pslow->next;
//             pfast = pfast->next;
//             if(pfast!=nullptr)
//                 pfast = pfast->next;
//         }
//         return nullptr;
//     }
//     ListNode* EntryNodeOfLoop(ListNode* pHead)
//     {
//         ListNode* meetingnode = MeetingNode(pHead);
//         if(meetingnode==nullptr)
//             return nullptr;

//         int loopnum=1;
//         ListNode* p1 = meetingnode;
//         while(p1->next!=meetingnode)
//         {
//             p1 = p1->next;
//             loopnum++;
//         }

//         p1=pHead;
//         for(int i=0;i<loopnum;i++)
//             p1=p1->next;

//         ListNode* p2 = pHead;
//         while(p1!=p2)
//         {
//             p1=p1->next;
//             p2=p2->next;
//         }

//         return p1;

//     }
// };
class Solution
{
public:
    ListNode *EntryNodeOfLoop(ListNode *pHead)
    {
        if (pHead == nullptr)
            return nullptr;
        ListNode *pbehind = pHead;
        ListNode *pfront = pHead;
        do
        {
            pbehind = pbehind->next;
            pfront = pfront->next;
            if (pfront == nullptr)
                return nullptr;
            pfront = pfront->next;
            if (pfront == nullptr)
                return nullptr;
        }while (pfront != pbehind);
        ListNode* pMeet = pbehind;
        pbehind=pbehind->next;
        int loop_num=1;
        while(pbehind!=pMeet)
        {
            loop_num++;
            pbehind=pbehind->next;
        }

        pbehind = pHead;
        pfront = pHead;
        for(int i=0;i<loop_num;i++)
        {
            pfront=pfront->next;
        }
        while(pfront!=pbehind)
        {
            pfront=pfront->next;
            pbehind=pbehind->next;
        }
        return pbehind;
    }
};

int main()
{
}