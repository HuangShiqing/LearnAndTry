#include <iostream>
#include <vector>
using namespace std;


bool Find(int target, vector<vector<int> > array) 
{
    // 数组表示,array.size()=4,array[0].size()=3
    //   1   2    8    9
    // [[4],[7],[10],[13]]
    //   6   8   11   15
    
    // 这个是colums，竖着的列数
    if(array.size()==0)
        return false;
    // 这个是rows，横着的行数
    if(array[0].size()==0)
        return false;

    int rows =  0;
    int columns = array.size()-1;

    while(true)
    {
        // 小于右上角，边界往左
        if(target<array[columns][rows])
        {
            if(columns>0)
                columns--;
            else            
                return false;
        }
        // 大于右上角，边界往下
        else if(target>array[columns][rows])
        {
            if(rows<array[0].size()-1)
                rows++;
            else
                return false;
        }
        else
        {
            return true;
        }
        
    }
        
}