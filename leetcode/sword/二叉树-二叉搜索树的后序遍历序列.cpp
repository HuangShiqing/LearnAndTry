//page 179
#include <iostream>
#include <vector>
using namespace std;

vector<int> vector_init(int *p, int len)
{
    vector<int> v(len);
    for (int i = 0; i < len; i++)
        v[i] = p[i];

    return v;
}

class Solution
{
public:
    // bool VerifySquenceOfBST(vector<int> sequence)
    // {
    //     //
    //     if(sequence.size()==0)
    //         return false;
    //     else if(sequence.size()==1)
    //         return true;
    //     // else if(sequence.size()==2)

    //     //     {
    //     //         if(sequence[0]<sequence[1])
    //     //             return true;
    //     //         else
    //     //             return false;
    //     //     }

    //     int root_val = sequence[sequence.size() - 1];
    //     int index_split = 0;
    //     for (int i = 0; i < sequence.size(); i++)
    //     {
    //         if (sequence[i] >= root_val)
    //         {
    //             index_split = i;
    //             break;
    //         }
    //     }

    //     for(int i=index_split;i<sequence.size();i++)
    //     {
    //         if(sequence[i]<root_val)
    //             return false;
    //     }

    //     vector<int> left_v(sequence.begin(),sequence.begin()+index_split);
    //     vector<int> right_v(sequence.begin()+index_split,sequence.end()-1);

    //     bool left =true;
    //     if(index_split>0)
    //         left = VerifySquenceOfBST(left_v);
    //     bool right=true;
    //     if(index_split<sequence.size()-1)
    //         bool right = VerifySquenceOfBST(right_v);

    //     return (left&&right);

    // }
    bool VerifySquenceOfBST_repeat(vector<int> &sequence, int left, int right)
    {
        if(right<=left)
            return true;

        int root = sequence[right];

        int split = -1;
        for (int i = 0; i < right; i++)
        {
            if (sequence[i] > root && split == -1)
            {
                split = i;
                continue;
            }
            //这里是出现新的小于才错误    
            if (sequence[i] < root && split != -1)
                return false;
        }
        //注意这里新的取值范围即可
        return VerifySquenceOfBST_repeat(sequence, left, split - 1) && VerifySquenceOfBST_repeat(sequence, split, right-1);
    }

    bool VerifySquenceOfBST(vector<int> sequence)
    {
        if (sequence.size() == 0)
            return false;
        return VerifySquenceOfBST_repeat(sequence, 0, sequence.size() - 1);
    }
};

int main()
{
    vector<int> sequence{5,7,6,9,11,10,8};
    Solution solution;

    bool result = solution.VerifySquenceOfBST(sequence);
    return 0;
}