#include <iostream>
#include <vector>

using namespace std;

// 207. 课程表
// 你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。
// 在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。
// 例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
// 请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

// 示例 1：
// 输入：numCourses = 2, prerequisites = [[1,0]]
// 输出：true
// 解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。

// 示例 2：
// 输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
// 输出：false
// 解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。

// -------------------第三次刷-----------------------
// 2021年6月21日10:19:51
// 准备第一次社招
// 思路: 能否完成课程就是判断是否存在死锁, 你的前提是我, 我的前提是你. 本质就是求是否为一个有向无环图DAG. 
// 判断是否为DAG的方法就是逐一将无输入的头node的输出移除. 最后所有node都能移除则是无环的. 如果是有环的, 那么
// 构成环的始终无法成为无输入的node被移除. 具体实现就是用一个vector<int>记录每个node的输入数量, 用vector<vector<int>>
// 记录每个node包含哪几个输出node. 逐一取出输入数量为0的node放到一个queue中, ...

#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> degrees(numCourses);// 每个node的入度, 也就是node的输入数量
        vector<vector<int>> adjacents(numCourses);// 每个node的包含哪几个输出node
        for(int i=0;i<prerequisites.size();i++){
            degrees[prerequisites[i][0]]++;
            adjacents[prerequisites[i][1]].push_back(prerequisites[i][0]);
        }

        queue<int> q;
        int num = 0;
        for(int i=0;i<degrees.size();i++){
            if(degrees[i]==0){
                q.push(i);
                num++;
            }
        }

        while(q.size()!=0){
            int tmp = q.front();
            q.pop();
            for(int i=0;i<adjacents[tmp].size();i++){
                degrees[adjacents[tmp][i]]--;
                if(degrees[adjacents[tmp][i]]==0){
                    q.push(adjacents[tmp][i]);
                    num++;
                }
            }
        }

        if(num==numCourses)
            return true;
        else
            return false;
    }
};