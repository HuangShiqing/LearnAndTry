//page 205
#include <iostream>
#include <vector>

using namespace std;

int Partition(int data[], int length, int start, int end)
{
    if (data == nullptr || length <= 0 || start < 0 || end >= length)
        throw "error";

    int index = start;
    swap(data[index], data[end]);

    int small = start - 1;
    for (index = start; index < end; index++)
    {
        if (data[index] < data[end])
        {
            small++;
            if (small != index)
                swap(data[index], data[small]);
        }
    }
    small++;
    swap(data[small], data[end]);
    return small;
}

class Solution
{
public:
    // bool check(int* num,int length,int number)
    // {
    //     int times=0;
    //     for(int i=0;i<length;i++)
    //     {
    //         if(num[i]==number)
    //             times++;
    //     }
    //     if(times*2<=length)
    //         return false;
    //     else
    //         return true;
    // }

    // int MoreThanHalfNum_Solution(vector<int> numbers) {

    //     if(numbers.size()==0)
    //         return 0;
    //     else if(numbers.size()==1)
    //         return numbers[0];
    //     else if(numbers.size()==2)
    //     {
    //         if(numbers[0]==numbers[1])
    //             return numbers[0];
    //         else
    //             return 0;
    //     }

    //     int num[numbers.size()]={0};
    //     int result = 0;

    //     for(int i=0;i<numbers.size();i++)
    //     {
    //         num[i] = numbers[i];
    //     }

    //     int middle = numbers.size()/2;
    //     int start = 0;
    //     int end = numbers.size()-1;

    //     result = Partition(num, numbers.size(), start, end);

    //     while(result!=middle)
    //     {
    //         if(result >middle)
    //         {
    //             end = result -1;
    //             result = Partition(num, numbers.size(), start, end);
    //         }
    //         else
    //         {
    //             start = result+1;
    //             result = Partition(num, numbers.size(), start, end);
    //         }
    //     }

    //     result = num[result];
    //     if(check(num,numbers.size(),result))
    //         return result;
    //     else
    //     {
    //         return 0;
    //     }

    // }
    int MoreThanHalfNum_Solution(vector<int> numbers)
    {
        if (numbers.size() == 0)
            return 0;

        int target;
        int count = 0;
        for (int i = 0; i < numbers.size(); i++)
        {
            if (count == 0)
            {
                target = numbers[i];
                count = 1;
                continue;
            }
            if(numbers[i]==target)
                count++;
            else
                count--;
        }

        count=0;
        for (int i = 0; i < numbers.size(); i++)
        {
            if(numbers[i]==target)
                count++;
        }
        if(count>numbers.size()/2)
            return target;
        else
            return 0;
    }
};

int main()
{
    // vector<int> vnumber{1,2,3,2,2,2,5,4,2};
    vector<int> vnumber{1, 2, 3, 2, 4, 2, 5, 2, 3};
    Solution solution;

    int result = solution.MoreThanHalfNum_Solution(vnumber);
    return 0;
}