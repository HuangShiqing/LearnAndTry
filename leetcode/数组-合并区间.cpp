#include <algorithm>
#include <vector>
using namespace std;

// 首先，我们将列表中的区间按照左端点升序排序
// 用数组 merged 存储最终的答案
// 如果当前区间的左端点在数组 merged 中最后一个区间的右端点之后，那么它们不会重合，我们可以直接将这个区间加入数组 merged
// 的末尾； 否则，它们重合，我们需要用当前区间的右端点更新数组 merged 中最后一个区间的右端点，将其置为二者的较大值

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> merged;
        if (intervals.size() == 0)
            return merged;
        sort(intervals.begin(), intervals.end());

        merged.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] > merged.back()[1])
                merged.push_back(intervals[i]);
            else
                merged.back()[1] = max(merged.back()[1], intervals[i][1]);
        }
        return merged;
    }
};