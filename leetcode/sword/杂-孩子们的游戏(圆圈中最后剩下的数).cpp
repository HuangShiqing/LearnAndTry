//page 300
#include <list>
#include <vector>
using namespace std;

class Solution
{
public:
    // int LastRemaining_Solution(int n, int m)
    // {
    //     if (n < 1 || m < 1)
    //         return -1;
    //     list<int> numbers;
    //     for (int i = 0; i < n; i++)
    //         numbers.push_back(i);

    //     list<int>::iterator current = numbers.begin();
    //     while (numbers.size() > 1)
    //     {

    //         for (int i = 1; i < m; i++)
    //         {
    //             current++;
    //             if (current == numbers.end())
    //                 current = numbers.begin();
    //         }
    //         list<int>::iterator next = ++current;
    //         if (next == numbers.end())
    //             next = numbers.begin();
    //         current--;
    //         numbers.erase(current);
    //         current = next;
    //     }
    //     return *current;
    // }
    int LastRemaining_Solution(int n, int m)
    {
        if (n < 1 || m < 1)
            return -1;
        vector<int> v;
        for (int i = 0; i < n; i++)
            v.push_back(i);

        int index_start = 0;
        int erase = index_start + m - 1;
        while (v.size() > 1)
        {
            //注意这里要用while
            while(erase >= v.size())
                erase -= v.size();
            v.erase(v.begin() + erase);
            index_start = erase;
            erase = index_start + m - 1;
        }
        return v[0];
    }
};

int main()
{
    int n = 0;
    int m = 0;
    Solution solution;
    solution.LastRemaining_Solution(n, m);
    return 0;
}