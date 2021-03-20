#include <vector>
#include <iostream>
using namespace std;

class Solution
{
public:
    vector<int> maxInWindows(const vector<int> &num, unsigned int size)
    {
        vector<int> v;
        if (size > num.size() || size == 0)
            return v;

        int left = 0;
        int right = size - 1;

        while (right <= num.size() - 1)
        {
            int temp_max = INT32_MIN;
            for (int i = left; i <= right; i++)
            {
                if (num[i] > temp_max)
                    temp_max = num[i];
            }
            v.push_back(temp_max);
            left++;
            right++;
        }
        return v;
    }
}; 
