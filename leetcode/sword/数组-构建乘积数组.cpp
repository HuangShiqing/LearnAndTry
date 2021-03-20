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