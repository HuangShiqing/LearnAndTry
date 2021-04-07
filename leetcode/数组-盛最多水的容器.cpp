#include <vector>
using namespace std;

// 双指针
// 一开始，我们考虑相距最远的两个柱子所能容纳水的面积
// 然后如果移动高的柱子，那么水的高度一定不会增加，且宽度一定减少，因此可以减少搜索空间，移动短的柱子

class Solution {
public:
    int maxArea(vector<int>& height) {
        int i = 0;
        int j = height.size()-1;
        int maxAres = -1;
        while(i<j)
        {
            maxAres = max((j-i)*min(height[i],height[j]),maxAres);

            if(height[i]<height[j])
                i++;
            else
                j--;
        }
        return maxAres;
    }
};