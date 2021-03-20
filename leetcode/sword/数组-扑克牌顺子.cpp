//page 298
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    // bool IsContinuous( vector<int> numbers ) {
    //     if(numbers.size()!=5)
    //         return false;

    //     sort(numbers.begin(),numbers.end());
    //     int num_0=0;
    //     int num_break=0;
    //     for(int i=0;i<numbers.size()-1;i++)
    //     {
    //         if(numbers[i]==0)
    //             continue;
    //         if(numbers[i]==numbers[i+1])
    //             return false;
    //     }
    //     for(int i=0;i<numbers.size();i++)
    //     {
    //         if(numbers[i]==0)
    //             num_0++;
    //     }
    //     for(int i=0;i<numbers.size()-1;i++)
    //     {
    //         if(numbers[i]==0)
    //             continue;
    //         if(numbers[i+1]-numbers[i]>1)
    //             num_break+=numbers[i+1]-numbers[i]-1;
    //     }

    //     if(num_break>num_0)
    //         return false;
    //     else
    //         return true;

    // }
    bool IsContinuous(vector<int> numbers)
    {
        if(numbers.size()<5)
            return false;
        
        sort(numbers.begin(),numbers.end());

        int king_num = 0;
        int split_num=0;
        for(int i=0;i<numbers.size()-1;i++)
        {
            if(numbers[i]==0)
                king_num++;
            else if(numbers[i+1]-numbers[i]==0)
                return false;
            else if(numbers[i+1]-numbers[i]==1)
                continue;
            else
                split_num+=numbers[i+1]-numbers[i]-1;
        }
        if(numbers[numbers.size()-1]==0)
                king_num++;

        return king_num>=split_num;

    }
};

int main()
{
    vector<int> numbers{1, 3, 2, 5, 4};

    Solution solution;
    bool result = solution.IsContinuous(numbers);
    return 0;
}