#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;


int main()
{
    vector<int> h_max{3,4,2,7,4,9,5,2,0,3};
    vector<int> h_min{3,4,2,7,4,9,5,2,0,3};

    //用greater初始化最小堆，[0]是最小的数
    make_heap(h_min.begin(),h_min.end(),greater<int>());
    //在数组末尾添加一个元素后重新保证[0]是最小的数
    h_min.push_back(5);
    push_heap(h_min.begin(),h_min.end(),greater<int>());
    //相当于push_heap的逆操作，把原本最小的数放到数组末尾，将次小的数放到[0]
    pop_heap(h_min.begin(),h_min.end(),greater<int>());
    h_min.pop_back();


    //用less初始化最大堆，[0]是最大的数
    make_heap(h_max.begin(),h_max.end(),less<int>());
    //在数组末尾添加一个元素后重新保证[0]是最大的数
    h_max.push_back(15);
    push_heap(h_max.begin(),h_max.end(),less<int>());
    //相当于push_heap的逆操作，把原本最大的数放到数组末尾，将次小的数放到[0]
    pop_heap(h_max.begin(),h_max.end(),less<int>());
    h_max.pop_back();

    // 另一种最大堆的方式
    priority_queue<int, vector<int>, less<int>> max_heap;
    max_heap.push(3);
    max_heap.pop();
    int a = max_heap.top();

    // 另一种最小堆的方式
    priority_queue<int, vector<int>, greater<int>> min_heap;
    min_heap.push(3);
    min_heap.pop();
    int a = min_heap.top();
    return 0;

}