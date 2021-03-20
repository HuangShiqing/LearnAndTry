//page 39
#include <iostream>
using namespace std;

class Solution
{
public:
    // Parameters:
    //        numbers:     an array of integers
    //        length:      the length of array numbers
    //        duplication: (Output) the duplicated number in the array number
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    // bool duplicate(int numbers[], int length, int *duplication)
    // {

    //     if (numbers == nullptr || length <= 0)
    //         return false;

    //     for (int i = 0; i < length; i++)
    //     {
    //         if (numbers[i] > length - 1 || numbers[i] < 0)
    //             return false;
    //     }

    //     for (int i = 0; i < length; i++)
    //     {
    //         while (numbers[i] != i)
    //         {
    //             if (numbers[i] == numbers[numbers[i]])
    //             {
    //                 *duplication = numbers[i];
    //                 return true;
    //             }
    //             swap(numbers[i],numbers[numbers[i]]);
    //         }
    //     }

    //     return false;
    // }
    //TODO:不理解
    bool duplicate(int numbers[], int length, int *duplication)
    {
        if (numbers == nullptr || length < 0)
            return false;

        for (int i = 0; i < length; i++)
        {
            if (numbers[i] < 0 || numbers[i] >= length)
                return false;
        }
        for (int i = 0; i < length; i++)
        {
            while (numbers[i] != i)
            {
                if (numbers[i] == numbers[numbers[i]])
                {
                    *duplication = numbers[i];
                    return true;
                }
                swap(numbers[i], numbers[numbers[i]]);
            }
        }
        return false;
    }
};

int main()
{
}