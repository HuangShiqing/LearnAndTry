//page 278
#include <vector>
#include <iostream>
#include <math.h>
using namespace std;

class Solution
{
public:
    // unsigned int FindFirstBitIs1(int num)
    // {
    //     int indexBit=0;
    //     while(((num&1)==0)&&(indexBit<8*sizeof(int)))
    //     {
    //         num=num>>1;
    //         indexBit++;
    //     }
    //     return indexBit;
    // }

    // bool IsBit1(int num,unsigned int indexBit)
    // {
    //     num=num>>indexBit;
    //     return (num&1);
    // }

    // void FindNumsAppearOnce(vector<int> data, int *num1, int *num2)
    // {
    //     if (data.size() < 2)
    //         return;

    //     int resultOR = 0;
    //     for (int i = 0; i < data.size(); i++)
    //         resultOR ^= data[i];
    //     unsigned int indexOf1 = FindFirstBitIs1(resultOR);

    //     *num1=*num2=0;
    //     for(int j=0;j<data.size();j++)
    //     {
    //         if(IsBit1(data[j],indexOf1))
    //             *num1 ^=data[j];
    //         else
    //             *num2 ^=data[j];
    //     }
    // }
    void FindNumsAppearOnce(vector<int> data, int *num1, int *num2)
    {
        if (data.size() == 0)
            return;

        int x = 0;
        for (int i = 0; i < data.size(); i++)
        {
            x ^= data[i];
        }
        unsigned int loc = 1;

        while ((x & loc) == 0)
        {
            loc = loc << 1;
        }
        vector<int> left;
        vector<int> right;
        for (int i = 0; i < data.size(); i++)
        {
            if ((data[i] & loc) == 0)
                left.push_back(data[i]);
            else
                right.push_back(data[i]);
        }

        for (int i = 0; i < left.size(); i++)
        {
            //TODO:这里会报错，但是提交又不会报错
            (*num1) ^= left[i];
        }
        for (int i = 0; i < right.size(); i++)
        {
            (*num2) ^= right[i];
        }
    }
    //题目2：其他数都出现3次
    int FindNumsAppearOnce(vector<int> data)
    {
        if (data.size() == 0)
            return 0;

        vector<int> v(32);
        for (int i = 0; i < data.size(); i++)
        {
            unsigned int bit = 1;
            for (int j = 0; j < 32; j++)
            {
                if ((data[i] & bit) != 0)
                {
                    v[j]++;
                }
                bit <<= 1;
            }
        }

        unsigned int sum = 0;
        // for (int i = 0; i < v.size(); i++)
        // {
        //     if (v[i] % 3 != 0)
        //     {
        //         sum += (pow(2, i)*(v[i] % 3));      
        //     }
        // }
        for (int i = v.size()-1; i >0 ; i--)
        {
            if (v[i] % 3 != 0)
                sum+=(v[i] % 3);
            sum<<=1;
        }
        return sum;
    }
};

int main()
{
    Solution solution;
    // vector<int> vdata{2, 4, 3, 6, 3, 2, 5, 5};
    // int *p1 = NULL;
    // int *p2 = NULL;
    // solution.FindNumsAppearOnce(vdata, p1, p2);

    vector<int> vdata{2, 2, 2, 3, 3, 3, 8};
    int r = solution.FindNumsAppearOnce(vdata);

    return 0;
}
