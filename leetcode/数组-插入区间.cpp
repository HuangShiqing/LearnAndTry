#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        // 依次扫描区间数组，分三种情况
        int i = 0;
        int n = intervals.size();

        // 1.遍历区间的右端点在插入区间的左端点的左侧,代表不重合,直接push
        while (i < n && intervals[i][1] < newInterval[0]) {
            result.push_back(intervals[i]);
            i++;
        }
        // 2.遍历区间的左端点<=插入区间的右端点,代表重合,进行合并
        while (i < n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(intervals[i][0], newInterval[0]);
            newInterval[1] = max(intervals[i][1], newInterval[1]);
            i++;
        }
        result.push_back(newInterval);
        // 3.在右侧
        while (i < n && intervals[i][0] > newInterval[1]) {
            result.push_back(intervals[i]);
            i++;
        }

        return result;
    }
};