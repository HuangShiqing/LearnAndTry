// 399. 除法求值
// 给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，其中 equations[i] = [Ai, Bi] 和 values[i]
// 共同表示等式 Ai / Bi = values[i] 。每个 Ai 或 Bi 是一个表示单个变量的字符串。 另有一些以数组 queries 表示的问题，其中
// queries[j] = [Cj, Dj] 表示第 j 个问题，请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。 返回 所有问题的答案
// 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0
// 替代这个答案。 注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。

// 示例 1：
// 输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries =
// [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]] 输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000] 解释： 条件：a
// / b = 2.0, b / c = 3.0 问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? 结果：[6.0, 0.5, -1.0, 1.0, -1.0 ]

// 示例 2：
// 输入：equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries =
// [["a","c"],["c","b"],["bc","cd"],["cd","bc"]] 输出：[3.75000,0.40000,5.00000,0.20000]

// 示例 3：
// 输入：equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
// 输出：[0.50000,2.00000,-1.00000,-1.00000]

// -------------------第二次刷-----------------------
// 2021年7月12日13:50:40
// 准备第一次社招
// 思路: 各个字母代表的具体数值是多少我们可以不关心, 只需要关心两个字母之间的关系即可. 因此建立一个有向图, 点是字母, 边是乘除系数
// 首先根据equations建立一个图, unordered_map<string, vector<pair<string, double>>> g, 头节点用map是因为后面要根据头节点find, 
// 一个头节点可以连接多个尾结点, 因此是一个vector, 每个尾结点和对应的头尾节点之间的系数作为pair. 
// 然后就是搜索环节, 能直接找到头尾节点是最好, 找不到就先找到头节点, 然后dfs去找尾节点, 过程中的每条边的系数都累积相乘

#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<double> res;

    bool dfs(unordered_map<string, vector<pair<string, double>>>& g, unordered_map<string, int>& visit, string val,
             const string& target, const double& path) {

        if (val == target) {
            res.push_back(path);
            return true;
        }

        for (int j = 0; j < g[val].size(); ++j) {
            //检查与val相连接的点，是否已经访问过了。没访问过继续dfs
            if (visit[g[val][j].first] == 0) {
                visit[g[val][j].first] = 1;
                bool found = dfs(g, visit, g[val][j].first, target, path * g[val][j].second);                
                visit[g[val][j].first] = 0;

                if(found == true)
                    return true;
            }
        }

        return false;
    }

    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values,
                                vector<vector<string>>& queries) {
        // string - string(double)  a连接b(b带上权值)
        unordered_map<string, vector<pair<string, double>>> g;
        unordered_map<string, int> visit;

        //构建无向图，a-b的value是3 的话 ，b-a是3的倒数
        for (int i = 0; i < equations.size(); ++i) {
            g[equations[i][0]].push_back(make_pair(equations[i][1], values[i]));
            g[equations[i][1]].push_back(make_pair(equations[i][0], 1.0 / values[i]));
        }

        for (int i = 0; i < queries.size(); ++i) {
            //如果queries[0]是不存在的，直接出结果：-1
            if (g.find(queries[i][0]) == g.end()) {
                res.push_back(-1.0);
                continue;
            }

            visit[queries[i][0]] = 1;
            bool found = dfs(g, visit, queries[i][0], queries[i][1], 1);
            visit[queries[i][0]] = 0;

            if( found == false)
                res.push_back(-1.0);
        }
        return res;
    }
};