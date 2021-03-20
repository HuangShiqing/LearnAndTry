#include <iostream>
#include <vector>
using namespace std;

int findLengthOfLCIS(vector<int> v)
{
    if(v.size()==0)
        return 0;
    // 至少要2个
    if(v.size()==1)
        return 1;

    int count=1;
    int max_count=INT32_MIN;
    // int index_start=0;
    // int index_end = 0;
    for(int i=1;i<v.size();i++)
    {
        if(v[i]>v[i-1])
        {
            count+=1;
            // index_end = i;
        }
        else
        {
            count =1;
        }
        if(count>max_count)
        {
            max_count = count;
            // index_start = i;
        }
            
    }
    return max_count;
    // return index_end-index_start;
}