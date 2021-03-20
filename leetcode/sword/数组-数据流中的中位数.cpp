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
