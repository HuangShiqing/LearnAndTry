// 剑指 Offer 56 - II. 数组中数字出现的次数 II
// 在一个数组 nums 中除一个数字只出现一次之外，其他数字都出现了三次。请找出那个只出现一次的数字。

// 示例 1：
// 输入：nums = [3,4,3,3]
// 输出：4

// 示例 2：
// 输入：nums = [9,1,7,9,7,9,7]
// 输出：1

// -------------------第三次刷-----------------------
// 2021年6月1日17:41:12
// 准备第一次社招
// 思路: 这题就不能用异或对消的办法了. 可以直接暴力一点, 统计32位上所有数出现1的次数, 每位%3!=0的则目标数字在该位也为1

#include <vector>
using namespace std;
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        vector<int> v(32);        
        unsigned int dight=1;
        for(int j=0;j<32;j++){            
            for(int i=0;i<nums.size();i++){
                // if((nums[i]&dight) == 1) //错误, 不能是等于1, 因为可能是等于2(10),4(100),8(1000)等
                if((nums[i]&dight)!= 0)
                    v[j]++;
            }
            dight=dight<<1;
        }

        unsigned int r=0;
        for(int j=0;j<32;j++){
            if(v[j]%3!=0)
                r = r|(1<<j);
        }
        return r;
    }
};

int main(){
    Solution s;
    vector<int> v{3,4,3,3};
    s.singleNumber(v);
    return -1;
}