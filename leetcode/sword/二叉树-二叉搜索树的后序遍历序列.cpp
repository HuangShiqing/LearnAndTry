// 剑指 Offer 33. 二叉搜索树的后序遍历序列
// 输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。如果是则返回 true，否则返回 false。假设输入的数组的任意两个数字都互不相同。

// 参考以下这颗二叉搜索树：

//      5
//     / \
//    2   6
//   / \
//  1   3
// 示例 1：
// 输入: [1,6,3,2,5]
// 输出: false
// 示例 2：
// 输入: [1,3,2,6,5]
// 输出: true

// 2021年05月15日10:44:48
// 准备第一次社招
// 思路: 
// 二叉搜索树定义： 左子树中所有节点的值 << 根节点的值；
//               右子树中所有节点的值 >> 根节点的值；
//               其左、右子树也分别为二叉搜索树
// 后序遍历的特点: 末尾是根节点
// [1,3,2,6,5]的root是5, 从左往右找到第一个比5大的为6, 那么6左边的都是左子叶, 
// 6以及右边的(这里右边没有)是右子叶, 如果6右边还有比root 5更小的, 则错误


#include <vector>
using namespace std;

class Solution {
public:
    bool verifyPostorder(vector<int>& postorder, int left, int right) {
        if(right<=left || left<0 || right>postorder.size()-1)
            return true;

        int split=-1;
        for(int i=left;i<right;i++){
            if(postorder[i]>postorder[right]&&split==-1){
                split = i;
            }
            if(postorder[i]<postorder[right]&&split!=-1){
                return false;
            }
        }
        if(split==-1)//记得处理全部都是左子叶, 找不到比root大的
            split=right;
        return verifyPostorder(postorder, left, split-1) && verifyPostorder(postorder, split, right-1);
    }
    bool verifyPostorder(vector<int>& postorder) {
        if(!postorder.size())
            return false;
        
        return verifyPostorder(postorder, 0, postorder.size()-1);
    }
};

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