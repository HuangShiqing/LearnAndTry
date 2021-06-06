// 剑指 Offer 41. 数据流中的中位数
// 如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。
// 如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。

// 例如，
// [2,3,4] 的中位数是 3
// [2,3] 的中位数是 (2 + 3) / 2 = 2.5
// 设计一个支持以下两种操作的数据结构：

// void addNum(int num) - 从数据流中添加一个整数到数据结构中。
// double findMedian() - 返回目前所有元素的中位数。

// 示例 1：
// 输入：
// ["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
// [[],[1],[2],[],[3],[]]
// 输出：[null,null,null,1.50000,null,2.00000]

// 示例 2：
// 输入：
// ["MedianFinder","addNum","findMedian","addNum","findMedian"]
// [[],[2],[],[3],[]]
// 输出：[null,null,2.00000,null,2.50000]

// -------------------第三次刷-----------------------
// 2021年5月18日14:31:58
// 准备第一次社招
// 思路: 用一个最大堆和一个最小堆来接受数据流, 最大堆max_heap用于存放较小的那些数, 最小堆min_heap用于存放较大的那些数. 中位数只取决于较小数中的最大数和较大数中的最小数.
// 注意: 需要插入一个数num的时候, 比如插入存放较小数的最大堆时max_heap, 需要保证这个数num比存放较大数的最小堆min_heap里的所有数都要小, 因此可以先把这个数num插入到后者, 然后从后者取出min_heap.top插入前者
class MedianFinder {
public:
    /** initialize your data structure here. */
    priority_queue<int, vector<int>, less<int>> max_heap;
    priority_queue<int, vector<int>, greater<int>> min_heap;
    MedianFinder() {

    }
    
    void addNum(int num) {
        if(max_heap.size()==min_heap.size()){
            min_heap.push(num);
            int top = min_heap.top();
            min_heap.pop();
            max_heap.push(top);
        }
        else{
            max_heap.push(num);
            int top = max_heap.top();
            max_heap.pop();
            min_heap.push(top);
        }
    }
    
    double findMedian() {
        if(max_heap.size()==min_heap.size()){
            return (max_heap.top()+min_heap.top())/2.0;//要2.0不是2
        }
        else
            return max_heap.top();
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

//page 214
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
public:
    // vector<int> gv_min;
    // vector<int> gv_max;

    // void Insert(int num)
    // {
    //     if ((gv_min.size() + gv_max.size() & 1) == 0) //偶数
    //     {
    //         if(num>gv_min[0]&&gv_min.size())
    //         {
    //             gv_min.push_back(num);
    //             push_heap(gv_min.begin(),gv_min.end(),greater<int>());

    //             num = gv_min[0];

    //             pop_heap(gv_min.begin(),gv_min.end(),greater<int>());
    //             gv_min.pop_back();
    //         }
    //         gv_max.push_back(num);
    //         push_heap(gv_max.begin(),gv_max.end(),less<int>());
    //     }
    //     else
    //     {
    //         if(num<gv_max[0]&&gv_max.size())
    //         {
    //             gv_max.push_back(num);
    //             push_heap(gv_max.begin(),gv_max.end(),less<int>());

    //             num = gv_max[0];

    //             pop_heap(gv_max.begin(),gv_max.end(),less<int>());
    //             gv_max.pop_back();
    //         }
    //         gv_min.push_back(num);
    //         push_heap(gv_min.begin(),gv_min.end(),greater<int>());
    //     }

    // }

    // double GetMedian()
    // {
    //     if(gv_min.size() + gv_max.size()==0)
    //         return 0;

    //     if((gv_min.size() + gv_max.size() & 1) == 0)
    //     {
    //         return (gv_max[0]+gv_min[0])/2.0;
    //     }
    //     else
    //     {
    //         return gv_max[0];
    //     }

    // }
    vector<int> h_max;
    vector<int> h_min;
    void Insert(int num)
    {
        if (h_max.size() <= h_min.size())
        {
            if (h_max.size() == 0)
            {
                h_max.push_back(num);
            }
            else
            {
                if (num > h_min[0])
                {
                    int temp = h_min[0];
                    pop_heap(h_min.begin(), h_min.end(), greater<int>());
                    h_min.pop_back();
                    h_min.push_back(num);
                    push_heap(h_min.begin(), h_min.end(), greater<int>());

                    h_max.push_back(temp);
                    push_heap(h_max.begin(), h_max.end(), less<int>());
                }
                else
                {
                    h_max.push_back(num);
                    push_heap(h_max.begin(), h_max.end(), less<int>());
                }
            }
        }
        else
        {
            if (num < h_max[0])
            {
                int temp = h_max[0];
                pop_heap(h_max.begin(), h_max.end(), less<int>());
                h_max.pop_back();
                h_max.push_back(num);
                push_heap(h_max.begin(), h_max.end(), less<int>());

                h_min.push_back(temp);
                push_heap(h_min.begin(), h_min.end(), greater<int>());
            }
            else
            {
                h_min.push_back(num);
                push_heap(h_min.begin(), h_min.end(), greater<int>());
            }
        }
    }

    double GetMedian()
    {
        if(h_max.size()==0&&h_min.size()==0)
            return 0;
        if((h_max.size()+h_min.size())%2==0)
        {
            return (h_max[0]+h_min[0])/2.0;
        }
        else
        {
            return h_max[0];
        }
        
    }
};

int main()
{
    vector<int> v_num{5, 2, 3, 4, 1, 6, 7, 0, 8};
    Solution solution;

    double middle;
    for (int i = 0; i < v_num.size(); i++)
    {
        solution.Insert(v_num[i]);
        middle = solution.GetMedian();
    }
    return 0;
}
