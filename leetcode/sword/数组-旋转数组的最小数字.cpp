//page 82
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
 // 超算那个思路不对，二分还是用来找lef和right相邻时退出
   int minNumberInRotateArray(vector<int> rotateArray)
    {
        if(rotateArray.size()==0)
            return 0;

        int left=0;
        int right=rotateArray.size()-1;
        int mid = (left+right)/2;
        while(left<=right)
        {
            // 当mid数大于left数，则转折点在mid的右边
            if(rotateArray[mid]>=rotateArray[left])
                left = mid;
            else
                right = mid;
            mid = (left+right)/2;

            // 当left和right相邻则找到退出
            if(abs(left-right)==1)
                return rotateArray[right]; 
        }
    }
    int minNumberInRotateArray(vector<int> rotateArray)
    {
        if(rotateArray.size()==0)
            return 0;

        int left=0;
        int right=rotateArray.size()-1;
        int mid = (left+right)/2;
        // while(rotateArray[left]>=rotateArray[right])
        while(1)
        {
            if(abs(left-right)==1)
            {
                return rotateArray[right];
            }

            //三者相等只能顺序查找
            if(rotateArray[left]==rotateArray[right]&&rotateArray[mid]==rotateArray[left])
            {
                int temp=left;
                for(int i=left+1;i<=right;i++)
                {
                    if(rotateArray[i]<rotateArray[temp])
                        temp=i;
                }
                return rotateArray[temp];
            }

            if(rotateArray[mid]>=rotateArray[left])
                left=mid;
            else
                right=mid;      
            mid = (left+right)/2;      
        }
    }
};
