#include <iostream>
#include <vector>
using namespace std;


int Partition(vector<int> vdata)
{
    if(vdata.size()==0)
        throw "error";// throw new exception("Invalid Parameter");

    int index=0;
    swap(vdata[index],vdata[vdata.size()-1]);

    int small = -1;
    for(index=0;index<vdata.size();index++)
    {
        if(vdata[index]<vdata[vdata.size()-1])
        {
            small++;
            if(small!=index)
                swap(vdata[index],vdata[small]);
        }
    }
    small++;
    swap(vdata[small],vdata[vdata.size()-1]);
    return small;
}
void QuickSort(vector<int> vdata)
{
    if(vdata.size()==0)
        throw "error";// throw new exception("Invalid Parameter");

    int index = Partition(vdata);
    if(index > 0)
        QuickSort(vdata(index,vdata.size()-1));
}

vector<int> BoubleSort(vector<int> input)
{
    for(int i=0;i<input.size()-1;i++)
    {
        for(int j=0;j<input.size()-1-i;j++)
        {
            if(input[j]>input[j+1])
            {
                swap(input[j],input[j+1]);
            }
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

    int p1 = middle;
    int p2 = end;
    vector<int> v;
    while (p1 >= start && p2 >= middle + 1)
    {
        if (data[p1] > data[p2])        
            v.push_back(data[p2--]);        
        else
            v.push_back(data[p1--]);
    }
    while (p1 >= start)
        v.push_back(data[p1--]);
    while (p2 >= middle + 1)
        v.push_back(data[p2--]);
    for (int i = 0; i < v.size(); i++)
        data[start + i] = v[i];
}

