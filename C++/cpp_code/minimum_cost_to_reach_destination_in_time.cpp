/*
https://leetcode.com/problems/minimum-cost-to-reach-destination-in-time/description/
1928. Minimum Cost to Reach Destination in Time

There is a country of n cities numbered from 0 to n - 1 where all the cities are connected by bi-directional roads. The
roads are represented as a 2D integer array edges where edges[i] = [xi, yi, timei] denotes a road between cities xi and
yi that takes timei minutes to travel. There may be multiple roads of differing travel times connecting the same two
cities, but no road connects a city to itself.

Each time you pass through a city, you must pay a passing fee. This is represented as a 0-indexed integer array
passingFees of length n where passingFees[j] is the amount of dollars you must pay when you pass through city j.

In the beginning, you are at city 0 and want to reach city n - 1 in maxTime minutes or less. The cost of your journey is
the summation of passing fees for each city that you passed through at some moment of your journey (including the source
and destination cities).

Given maxTime, edges, and passingFees, return the minimum cost to complete your journey, or -1 if you cannot complete it
within maxTime minutes.



Example 1:



Input: maxTime = 30, edges = [[0,1,10],[1,2,10],[2,5,10],[0,3,1],[3,4,10],[4,5,15]], passingFees = [5,1,2,20,20,3]
Output: 11
Explanation: The path to take is 0 -> 1 -> 2 -> 5, which takes 30 minutes and has $11 worth of passing fees.
Example 2:



Input: maxTime = 29, edges = [[0,1,10],[1,2,10],[2,5,10],[0,3,1],[3,4,10],[4,5,15]], passingFees = [5,1,2,20,20,3]
Output: 48
Explanation: The path to take is 0 -> 3 -> 4 -> 5, which takes 26 minutes and has $48 worth of passing fees.
You cannot take path 0 -> 1 -> 2 -> 5 since it would take too long.
Example 3:

Input: maxTime = 25, edges = [[0,1,10],[1,2,10],[2,5,10],[0,3,1],[3,4,10],[4,5,15]], passingFees = [5,1,2,20,20,3]
Output: -1
Explanation: There is no way to reach city 5 from city 0 within 25 minutes.


Constraints:

1 <= maxTime <= 1000
n == passingFees.length
2 <= n <= 1000
n - 1 <= edges.length <= 1000
0 <= xi, yi <= n - 1
1 <= timei <= 1000
1 <= passingFees[j] <= 1000
The graph may contain multiple edges between two nodes.
The graph does not contain self loops.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <map>
#include <numeric>
using namespace std;

class Solution {
public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        int n = passingFees.size();
        vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>>());
        for (vector<int>& e : edges) {
            graph[e[0]].push_back({e[1], e[2]});
            graph[e[1]].push_back({e[0], e[2]});
        }

        vector<vector<int>> min_cost(n, vector<int>(maxTime + 1, INT_MAX));
        min_cost[0][0] = passingFees[0];

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        pq.push({min_cost[0][0], 0, 0});  // cost, time, node
        while (!pq.empty()) {
            auto [cur_cost, cur_time, cur_node] = pq.top();
            pq.pop();

            if (cur_cost > min_cost[cur_node][cur_time]) {
                continue;
            }

            if (cur_node == n - 1) {
                return cur_cost;
            }

            for (auto& [next_node, time_cost] : graph[cur_node]) {
                int next_time = cur_time + time_cost;
                if (next_time > maxTime) {
                    continue;
                }

                if (cur_cost + passingFees[next_node] < min_cost[next_node][next_time]) {
                    min_cost[next_node][next_time] = cur_cost + passingFees[next_node];
                    pq.push({cur_cost + passingFees[next_node], next_time, next_node});
                }
            }
        }
        return -1;
    }
};

/*
问题在于你试图用两个一维数组 min_cost 和 min_time
分别追踪最小费用和最小时间，但这道题有两个相互竞争的维度：一条路径可能费用高但时间短，另一条费用低但时间长，两者都可能是最优解的一部分，你不能独立地剪枝。
具体 bug：当你 push 到 pq 的时候，第二个分支里用的是
min_time[next_node]（刚更新的全局最小时间），而不是当前路径的实际时间 cur_time + time_cost。这混淆了不同路径的状态。
正确做法：状态需要是 (node, time)，用 min_cost[node][time] 记录到达 node 恰好花费 time 时间的最小费用：

这个版本修复了之前 push 时用错时间的 bug，但核心问题还在：两个一维数组的剪枝策略会漏掉有效状态。
考虑这个场景：到达节点 X 有两条路径：

路径 A：cost=10, time=5 → 更新了 min_cost[X]=10, min_time[X]=5
路径 B：cost=15, time=3

路径 B 到达时，cur_cost(15) > min_cost[X](10) 且 cur_time(3) < min_time[X](5)，所以不会被剪枝，这没问题。但假设后来：

路径 C：cost=12, time=4

路径 C 到达时，cur_cost(12) > min_cost[X](10) 且 cur_time(4) < min_time[X](3)（被路径 B
更新了）。两个都大于已知最优，被剪掉了。但路径 C 可能在后续路径上比 A 和 B 都好——它费用比 B 低，时间比 A
短，是一个有价值的"中间态"。 这种剪枝本质上是一种启发式，在很多测试用例上能过，但不能保证正确性。安全的做法还是用
min_cost[node][time] 二维状态，这样每个 (node, time) 组合都被精确追踪，不会误剪。 实际上这个版本在 LeetCode 上应该会 WA
或 TLE 在某些边界 case 上。建议还是用上一个二维 min_cost[node][time] 的方案。
 */
class wrong_Solution {
public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        int n = passingFees.size();
        vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>>());
        for (vector<int>& e : edges) {
            graph[e[0]].push_back({e[1], e[2]});
            graph[e[1]].push_back({e[0], e[2]});
        }

        vector<int> min_cost(n, INT_MAX);
        min_cost[0] = passingFees[0];

        vector<int> min_time(n, INT_MAX);
        min_time[0] = 0;

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        pq.push({min_cost[0], min_time[0], 0});  // cost, time, node
        while (!pq.empty()) {
            auto [cur_cost, cur_time, cur_node] = pq.top();
            pq.pop();

            if (cur_cost > min_cost[cur_node] && cur_time > min_time[cur_node]) {
                continue;
            }

            if (cur_node == n - 1) {
                return cur_cost;
            }

            for (auto& [next_node, time_cost] : graph[cur_node]) {
                if (cur_time + time_cost > maxTime) {
                    continue;
                }

                if (cur_cost + passingFees[next_node] < min_cost[next_node]) {
                    min_cost[next_node] = cur_cost + passingFees[next_node];
                    pq.push({cur_cost + passingFees[next_node], cur_time + time_cost, next_node});
                }

                if (cur_time + time_cost < min_time[next_node]) {
                    min_time[next_node] = cur_time + time_cost;
                    pq.push({cur_cost + passingFees[next_node], cur_time + time_cost, next_node});
                }
            }
        }
        return -1;
    }
};
