#include <algorithm>
#include <vector>
using namespace std;

// 56. 合并区间
// 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间。

// 示例 1：
// 输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
// 输出：[[1,6],[8,10],[15,18]]
// 解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].

// 示例 2：
// 输入：intervals = [[1,4],[4,5]]
// 输出：[[1,5]]
// 解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。

// -------------------第二次刷-----------------------
// 2021年6月10日11:42:59
// 准备第一次社招
// 思路: 
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