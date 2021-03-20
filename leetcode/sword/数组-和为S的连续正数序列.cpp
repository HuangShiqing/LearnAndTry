//page:282
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
public:
    // vector<vector<int>> FindContinuousSequence(int sum)
    // {
    //     int start = 1;
    //     int end = 2;

    //     int sum_temp = 0;
    //     vector<int> v;
    //     vector<vector<int>> v2;
    //     for (int i = 1; i <= end; i++)
    //     {
    //         sum_temp += i;
    //         v.push_back(i);
    //     }

    //     //TODO:不懂这里为什么停止条件是（sum+1）/2
    //     int middle = (sum + 1) / 2;
    //     while (start < middle)
    //     {
    //         if (sum_temp == sum)
    //         {
    //             v2.push_back(v);                
    //             end++;
    //             v.push_back(end);
    //             sum_temp += end;
    //         }
    //         else if (sum_temp < sum)
    //         {

    //             end++;
    //             v.push_back(end);
    //             sum_temp += end;
    //         }
    //         else
    //         {
    //             sum_temp -= start;
    //             v.erase(v.begin());
    //             start++;
    //         }
    //     }
    //     return v2;
    // }
    vector<vector<int>> FindContinuousSequence(int sum)
    {
        vector<vector<int>> vv;
        
        if(sum<3)
            return vv;
        if(sum==3)
        {
            vector<int> v{1,2};
            vv.push_back(v);
            return vv;
        }

        int p1=1;
        int p2=2;
        while(p1<=sum/2)
        {
            int temp_sum=0;
            int temp_p=p1;
            while(temp_p<=p2)
            {
                temp_sum+=temp_p;
                temp_p++;
            }
            if(temp_sum==sum)
            {
                vector<int> v;
                temp_p=p1;
                while(temp_p<=p2)
                {
                    v.push_back(temp_p);
                    temp_p++;
                }
                vv.push_back(v);
                p1++;
            }
            else if (temp_sum<sum)
                p2++;
            else
                p1++;
            
        }
        return vv;
            
    }
};

int main()
{
    Solution solution;
    solution.FindContinuousSequence(15);
    return 0;
}