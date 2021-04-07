#include <algorithm>
#include <vector>
using namespace std;

// 没懂
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i = nums.size() - 2;
        // 步骤1：从后向前查找第一个顺序对 (i,i+1)(i,i+1)，满足 a[i] < a[i+1]a[i]<a[i+1]。「较小数」即为 a[i]
        while (i >= 0 && nums[i] >= nums[i + 1])
            i--;
        // 步骤2：在区间 [i+1,n)[i+1,n) 中从后向前查找第一个元素 jj 满足 a[i] < a[j]a[i]<a[j]。较大数即为 a[j]
        if (i >= 0) {  //如果在步骤 1 找不到顺序对，说明当前序列已经是一个降序序列，即最大的序列，我们直接跳过步骤 2
                       //执行步骤 3，即可得到最小的升序序列
            int j = nums.size() - 1;
            while (j >= 0 && nums[i] >= nums[j])
                j--;
            swap(nums[i], nums[j]);
        }
        // 步骤3：反转区间 [i+1,n)[i+1,n) 使其变为升序，而无需对该区间进行排序
        reverse(nums.begin() + 1 + i, nums.end());
    }
};