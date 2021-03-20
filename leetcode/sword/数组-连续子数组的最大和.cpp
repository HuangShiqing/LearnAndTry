//page 218
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    // int FindGreatestSumOfSubArray(vector<int> array) {
    //     if(array.size()==0)
    //         return 0;

    //     int nGreatestSum = -1;
    //     int nCurSum = 0;
    //     for(int i =0;i<array.size();i++)
    //     {
    //         if(nCurSum<0)
    //             nCurSum = array[i];
    //         else
    //             nCurSum += array[i];

    //         if(nCurSum>nGreatestSum)
    //             nGreatestSum = nCurSum;
    //     }
    //     return nGreatestSum;
    // }
    int FindGreatestSumOfSubArray(vector<int> array)
    {
        if (array.size() == 0)
            return 0;

        int sum = 0;
        int great_sum = INT32_MIN;
        for (int i = 0; i < array.size(); i++)
        {            
            
            if (sum < 0)
                sum = array[i];
            else
                sum += array[i];

            if (sum > great_sum)
                great_sum = sum;
        }
        return great_sum;
    }
};

int main()
{
    Solution solution;
    vector<int> array{1, -2, 3, 10, -4, 7, 2, -5};

    int result = solution.FindGreatestSumOfSubArray(array);
}