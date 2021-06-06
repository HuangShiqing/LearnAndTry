// 剑指 Offer 66. 构建乘积数组
// 给定一个数组 A[0,1,…,n-1]，请构建一个数组 B[0,1,…,n-1]，其中 B[i] 的值是数组 A 中除了下标 i 以外的元素的积, 
// 即 B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。

// 示例:
// 输入: [1,2,3,4,5]
// 输出: [120,60,40,30,24]

// -------------------第三次刷-----------------------
// 2021年6月4日11:30:37
// 准备第一次社招
// 思路: 上下三角, 上三角为数组C, 下三角为数组D
// B0= 1 * A1 * A2 * A3 * A4
// B1= A0 * 1 * A2 * A3 * A4
// B2= A0 * A1 * 1 * A3 * A4
// B3= A0 * A1 * A2 * 1 * A4
// B4= A0 * A1 * A2 * A3 * 1

class Solution {
public:
    vector<int> constructArr(vector<int>& a) {
        vector<int> C(a.size());
    }
};


//page 312
#include <vector>
using namespace std;

class Solution
{
public:
    // vector<int> multiply(const vector<int> &A)
    // {
    //     if(A.size()==0)
    //         return A;
        
    //     vector<int> v(A.size());
    //     vector<int> left(A.size());
    //     vector<int> right(A.size());

    //     for (int i = 0; i < A.size(); i++)
    //     {
    //         if (i == 0)
    //         {
    //             left[0] = 1;
    //             continue;
    //         }
    //         left[i] = left[i - 1] * A[i-1];
    //     }

    //     for (int i = A.size() - 1; i > -1; i--)
    //     {
    //         if (i == A.size() - 1)
    //         {
    //             right[A.size() - 1] = 1;
    //             continue;
    //         }
    //         right[i] = right[i + 1] * A[i+1];
    //     }

    //     for(int i=0;i<A.size();i++)
    //     {
    //         v[i]=left[i]*right[i];
    //     }
    //     return v;
    //     // vector<int>::iterator iter = right.end()-1;
    //     // while(iter!=right.begin()-1)
    //     // {

    //     // }
    // }
    vector<int> multiply(const vector<int> &A)
    {
        vector<int> B(A.size());
        if(A.size()==0)
            return B;
        
        vector<int> C(A.size());
        vector<int> D(A.size());

        C[0]=1;
        D[A.size()-1]=1;
        for(int i=1;i<A.size();i++)
        {
            C[i]=A[i-1]*C[i-1];
        }
        for(int i=A.size()-2;i>=0;i--)
        {
            D[i]=A[i+1]*D[i+1];
        }

        for(int i=0;i<A.size();i++)
        {
            B[i] = C[i]*D[i];
        }
        return B;
    }
};


int main()
{
    vector<int> A{1,2,3,4,5};
    Solution solution;
    vector<int> B = solution.multiply(A);
    return 0;
}