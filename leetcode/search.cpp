#include <vector>

using namespace std;

int BinarySearch(vector<int> v, int k)
{
    int left = 0;
    int right = v.size() - 1;
    int middle = (left + right) / 2;

    while (left <= right)
    {
        if (v[middle] == k)
            return middle;
        else if (v[middle] < k)
            left = middle + 1;
        else 
            right = middle - 1;

        middle = (left + right) / 2;
    }
    return -1;
}


int main()
{
    vector<int> v{1,2,5,8,9,10};
    int r = BinarySearch(v,11);

    return 0;
}