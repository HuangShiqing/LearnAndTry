//page 209
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Solution {
public:
    // vector<int> BoubleSort(vector<int> input)
    // {
    //     for(int i=0;i<input.size()-1;i++)
    //     {
    //         for(int j=0;j<input.size()-1-i;j++)
    //         {
    //             if(input[j]>input[j+1])
    //             {
    //                 swap(input[j],input[j+1]);
    //             }
    //         }
    //     }
    //     return input;
    // }

    // vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
    //     vector<int> empty;
    //     if(input.size()==0)
    //         return empty;
    //     else if(k>input.size())
    //         return empty;
            
    //     vector<int> input_sored = BoubleSort(input);
    //     vector<int> v(input_sored.begin(),input_sored.begin()+k);
    //     return v;
    // }
    int Partition(vector<int>& data,int start,int end)
    {
        swap(data[start],data[end]);

        int small=start-1;
        for(int i=start;i<end;i++)
        {
            if(data[i]<data[end])
            {
                small++;
                if(small!=i)
                    swap(data[small],data[i]);
                
            }
        }
        swap(data[end],data[++small]);
        return small;
    }
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k)
    {
        vector<int> v;
        if(input.size()==0||k<=0||k>input.size())
            return v;
        int index = Partition(input,0,input.size()-1);
        while (index!=k-1)
        {
            if(index<k-1)
                index = Partition(input,index+1,input.size()-1);
            else            
                index = Partition(input,0,index-1);                        
        }

        vector<int> v1(input.begin(),input.begin()+k-1);

        return v1;

    }   

    int Partition(vector<int>& data,int start,int end)
    {
        swap(data[start],data[end]);
        int small=start-1;
        for(int i=start;i<end;i++)
        {
            if(data[i]<data[end])
            {
                small++;
                if(small!=i)
                {
                    swap(data[i],data[small]);
                }
            }
        }
        swap(data[small],data[end]);
        return small;
    }

    vector<int> h_max;
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k)
    {
        if(input.size()==0||k<=0||k>input.size())
            return h_max;
        for(int i=0;i<input.size();i++)
        {
            if(h_max.size()<k)
            {
                h_max.push_back(input[i]);
                push_heap(h_max.begin(),h_max.end(),less<int>());
            }
            else
            {
                if(input[i]>h_max[0])
                    continue;
                else
                {
                    pop_heap(h_max.begin(),h_max.end(),less<int>());
                    h_max.pop_back();

                    h_max.push_back(input[i]);
                    push_heap(h_max.begin(),h_max.end(),less<int>());
                }
                
            }
            
        }
        return h_max;
    }
};



int main()
{
    Solution solution;
    vector<int> vinput;//,1,6,2,7,3,8
    int k =4;
    vector<int> vresult = solution.GetLeastNumbers_Solution(vinput, k);
    return 0;
}