//page 129
#include <iostream>
#include <vector>
using namespace std;

// 需要保证稳定性，冒泡法，时间复杂度为n2
void reOrderArray(vector<int> &array)
{
    if(array.size()==0)
        return;
    for(int i=0;i<array.size()-1;i++)
    {
        // -i是因为和冒泡一样，要排到后面的数每次都会被弄到最后，所以数组后面的是有序的
        for(int j=0;j<array.size()-1-i;j++)
        {
            if(array[j]%2==0&&array[j+1]%2==1)
                swap(array[j],array[j+1]);
        }
    }
}

// 不考虑稳定性
// 可以用头尾指针，只需要遍历一遍，时间复杂度为n
void reOrderArray_2(vector<int> &array)
{
    if(array.size()==0)
        return;
    
    int index_begain = 0;
    int index_end = array.size()-1;

    // 直到两个指针相遇
    while(index_begain<index_end)
    {
        // 让头指针指向要在后的偶数
        while(array[index_begain]%2!=0&&index_begain<index_end)
            index_begain++;
        
        // 让头指针指向要在后的偶数
        while(array[index_end]%2==0&&index_begain<index_end)
            index_end--;
        
        if(index_begain<index_end)
            swap(array[index_begain],array[index_end]);

    return 0;
}