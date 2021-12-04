#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    //初始化
    //初始化空vector
    vector<int> v;
    //初始化大小和容量都为10的空vector. 不能直接用于类成员变量的声明, 要先声明vector<int> v;然后在构造函数里v.resize(10);
    vector<int> v1(10);
    //初始化大小和容量都为10,值都为1的vector
    vector<int> v2(10, 1);
    vector<int> v3{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> v4(v3.begin(), v3.end());
    vector<vector<int>> dp(10, vector<int>(10, 0));//初始化指定大小的二维v

    //访问
    int a = v2[0];
    a = v3.front();
    a = v3.back();
    a = *v3.begin();
    a = *(v3.end() - 1);

    //查看属性
    int size = v2.size();
    bool is_empty = v2.empty();

    //插入和移除
    //在末尾插入一个数
    v2.push_back(3);
    v.push_back(2);
    //移除最后一个数
    v2.pop_back();

    //移除第一个数
    v2.erase(v2.begin());
    //移除第二个数
    v2.erase(v2.begin() + 1);

    // int b = v2.insert(v2.begin(),3);
    // v2.insert(1);

    //反转vector
    //在原本v上进行反转
    reverse(v3.begin(),v3.end());
    //不改变原本v，将反转结果拷贝到一个新的同大小的v里
    vector<int> v5(v3.size());
    reverse_copy(v3.begin(),v3.end(),v5.begin());

    //获取内存指针
    int* p = v5.data();

    //交换
    swap(v3[1], v3[2]);
    iter_swap(v3.begin() + 1, v3.begin() + 2);

    //去重
    sort(v1.begin(), v1.end());
    vector<int>::iterator new_end = unique(v1.begin(), v1.end());
    vector<int> v_uniqued(v1.begin(),new_end);
    return 0;
}
