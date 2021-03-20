#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// int Partition(vector<int> vdata)
// {
//     if (vdata.size() == 0)
//         throw "error"; // throw new exception("Invalid Parameter");

//     int index = 0;
//     swap(vdata[index], vdata[vdata.size() - 1]);

//     int small = -1;
//     for (index = 0; index < vdata.size(); index++)
//     {
//         if (vdata[index] < vdata[vdata.size() - 1])
//         {
//             small++;
//             if (small != index)
//                 swap(vdata[index], vdata[small]);
//         }
//     }
//     small++;
//     swap(vdata[small], vdata[vdata.size() - 1]);
//     return small;
// }
// void QuickSort(vector<int> vdata)
// {
//     if(vdata.size()==0)
//         throw "error";// throw new exception("Invalid Parameter");

//     int index = Partition(vdata);
//     if(index > 0)
//         QuickSort(vdata(index,vdata.size()-1));
// }

// int Partition(int data[], int length, int start, int end)
// {
//     if (data == nullptr || length <= 0 || start < 0 || end >= length)
//         throw "error";

//     int index = start;
//     swap(data[index], data[end]);

//     int small = start - 1;
//     for (index = start; index < end; index++)
//     {
//         if (data[index] < data[end])
//         {
//             small++;
//             if (small != index)
//                 swap(data[index], data[small]);
//         }
//     }
//     small++;
//     swap(data[small], data[end]);
//     return small;
// }

// void QuickSort(int data[], int length, int start, int end)
// {
//     if (start == end)
//         return;
//     int index = Partition(data, length, start, end);
//     if (index > start)
//         QuickSort(data, length, start, index - 1);
//     if (index < end)
//         QuickSort(data, length, index + 1, end);
// }
// void BubleSort(int data[], int length)
// {
//     for (int i = 0; i < length - 1; i++) //如果有n个数，就要连续排序n - 1 次
//     {
//         for (int j = 0; j < length - 1 - i; j++) //执行每一次比较的次数
//         {
//             if (data[j] > data[j + 1])      //如果这个数比前面的大
//                 swap(data[j], data[j + 1]); //把a[j] 和 a[j + 1] 进行交换
//         }
//     }
// }
int Partition(vector<int> &vdata, int start, int end)
{
    if (vdata.size() == 0 || start < 0 || end > vdata.size() - 1)
        throw "error";
    swap(vdata[start], vdata[end]);
    int small = start - 1;
    for (int i = start; i < end; i++)
    {
        if (vdata[i] < vdata[end])
        {
            small++;
            if (small != i)
                swap(vdata[i], vdata[small]);
        }
    }
    swap(vdata[++small], vdata[end]);
    return small;
}

void QuickSort(vector<int> &vdata, int start, int end)
{
    if (start == end)
        return;

    int index = Partition(vdata, start, end);

    if (index > start)
        QuickSort(vdata, start, index - 1);
    if (index < end)
        QuickSort(vdata, index + 1, end);
}

vector<int> BoubleSort(vector<int> input)
{
    for (int i = 0; i < input.size() - 1; i++)
    {
        for (int j = 0; j < input.size() - 1 - i; j++)
        {
            if (input[j] > input[j + 1])
                swap(input[j], input[j + 1]);
        }
    }
    return input;
}

void MergeSort(vector<int> &data, int start, int end)
{
    if (end - start == 0)
        return;
    if (end - start == 1)
    {
        if (data[start] > data[end])
            swap(data[start], data[end]);
        return;
    }

    int middle = (start + end) / 2;
    MergeSort(data, start, middle);
    MergeSort(data, middle + 1, end);

    vector<int> v;
    int p1 = start;
    int p2 = middle + 1;
    while (p1 <= middle && p2 <= end)
        v.push_back(data[p1] < data[p2] ? data[p1++] : data[p2++]);
    while (p1 <= middle)
        v.push_back(data[p1++]);
    while (p2 <= end)
        v.push_back(data[p2++]);

    for (int i = 0; i < v.size(); i++)
        data[start + i] = v[i];
}

void InsertSort(vector<int> &data)
{
    for (int i = 1; i < data.size(); i++)
    {
        int pre = i - 1;
        int cur = data[i];
        while (data[pre] > cur && pre >= 0)
        {
            data[pre + 1] = data[pre];
            pre--;
        }
        data[pre + 1] = cur;
    }
}

bool cmp_fun(vector<int> v1, vector<int> v2)
{
    //前者小于后者则为升序
    if (v1.size() <= v2.size())
        return true;
    else
        return false;
}

int main()
{
    // vector<int> vdata{5, 3, 8, 9, 2, 6, 7, 4};
    // int small = Partition(vdata);
    // int data[6]={32, 1, 52, 25, 88, 56};//{6,3,4,2,7,0,8,1,5,9};
    // BubleSort(data,10);
    // QuickSort(data,6,0,5);

    // vector<int> vdata{32, 1, 52, 25, 88, 56};
    // int data[6]={32, 1, 52, 25, 88, 56};//{6,3,4,2,7,0,8,1,5,9};
    // QuickSort(vdata,0,5);

    // vector<vector<int>> vv{{1, 2, 4, 6, 3, 6}, {4, 3, 2, 5}, {6, 3, 2, 1, 5}};
    // sort(vv.begin(), vv.end(), cmp_fun);

    vector<int> vdata{5, 3, 8, 9, 2, 6, 7, 4};
    // MergeSort(vdata, 0, vdata.size() - 1);
    InsertSort(vdata);
    return 0;
}
