/*
https://leetcode.com/problems/minimum-cost-to-buy-apples/description/
2473. Minimum Cost to Buy Apples
You are given a positive integer n representing n cities numbered from 1 to n. You are also given a 2D array roads,
where roads[i] = [ai, bi, costi] indicates that there is a bidirectional road between cities ai and bi with a cost of
traveling equal to costi.

You can buy apples in any city you want, but some cities have different costs to buy apples. You are given the 1-based
array appleCost where appleCost[i] is the cost of buying one apple from city i.

You start at some city, traverse through various roads, and eventually buy exactly one apple from any city. After you
buy that apple, you have to return back to the city you started at, but now the cost of all the roads will be multiplied
by a given factor k.

Given the integer k, return a 1-based array answer of size n where answer[i] is the minimum total cost to buy an apple
if you start at city i.



Example 1:


Input: n = 4, roads = [[1,2,4],[2,3,2],[2,4,5],[3,4,1],[1,3,4]], appleCost = [56,42,102,301], k = 2
Output: [54,42,48,51]
Explanation: The minimum cost for each starting city is the following:
- Starting at city 1: You take the path 1 -> 2, buy an apple at city 2, and finally take the path 2 -> 1. The total cost
is 4 + 42 + 4 * 2 = 54.
- Starting at city 2: You directly buy an apple at city 2. The total cost is 42.
- Starting at city 3: You take the path 3 -> 2, buy an apple at city 2, and finally take the path 2 -> 3. The total cost
is 2 + 42 + 2 * 2 = 48.
- Starting at city 4: You take the path 4 -> 3 -> 2 then you buy at city 2, and finally take the path 2 -> 3 -> 4. The
total cost is 1 + 2 + 42 + 1 * 2 + 2 * 2 = 51. Example 2:


Input: n = 3, roads = [[1,2,5],[2,3,1],[3,1,2]], appleCost = [2,3,1], k = 3
Output: [2,3,1]
Explanation: It is always optimal to buy the apple in the starting city.


Constraints:

2 <= n <= 1000
1 <= roads.length <= 2000
1 <= ai, bi <= n
ai != bi
1 <= costi <= 105
appleCost.length == n
1 <= appleCost[i] <= 105
1 <= k <= 100
There are no repeated edges.
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

/*
你的思路完全正确。从每个起点 i 出发，到城市 j 买苹果的总花费是 (k+1) * dist(i,j) +
appleCost[j]，因为去和回的路程加起来是 (1+k) * dist。 优化的关键：反转思路，从所有终点同时出发跑一次 Dijkstra。
你现在的做法是 N 次 Dijkstra，每次从一个起点出发。但可以这样想：创建一个虚拟超级源点，连接到每个城市 j，边权为
appleCost[j]。然后从这个超级源点跑一次 Dijkstra，到达城市 i 的最短距离就是"从某个最优城市 j 买苹果然后走到 i
的最小花费"。 但因为路费要乘以 (k+1)，实际操作更简单——不需要真的建超级源点，直接用多源 Dijkstra：

核心思想：把每个城市 j 想象成"苹果源"，初始代价是 appleCost[j]。Dijkstra 向外扩展时，边权是 (k+1) *
toll（来回路费）。当这个"波"传播到城市 i 时，dist[i] 就自然记录了从 i 出发去某个最优城市买苹果再回来的最小总花费。 从 N
次 Dijkstra 优化到了一次 Dijkstra，时间复杂度从 O(N * E log N) 降到 O(E log N)。
*/
class Solution {
public:
    vector<long long> minCost(int n, vector<vector<int>>& roads, vector<int>& appleCost, int k) {
        vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>>());
        for (vector<int>& r : roads) {
            int city_a = r[0] - 1;
            int city_b = r[1] - 1;
            int cost = r[2];
            graph[city_a].push_back({city_b, cost});
            graph[city_b].push_back({city_a, cost});
        }

        // base cost without traveling to different cities
        vector<long long> rst(appleCost.begin(), appleCost.end());
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        for (int i = 0; i < n; i++) {
            pq.push({appleCost[i], i});
        }

        while (!pq.empty()) {
            auto [cur_cost, cur_city] = pq.top();
            pq.pop();

            if (cur_cost > rst[cur_city]) {
                continue;
            }

            for (auto& [next_city, toll] : graph[cur_city]) {
                long long new_cost = cur_cost + (k + 1) * toll;
                if (new_cost < rst[next_city]) {
                    rst[next_city] = new_cost;
                    pq.push({new_cost, next_city});
                }
            }
        }
        return rst;
    }
};
