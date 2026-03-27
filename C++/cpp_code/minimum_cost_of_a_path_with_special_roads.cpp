/*
https://leetcode.com/problems/minimum-cost-of-a-path-with-special-roads/description/
2662. Minimum Cost of a Path With Special Roads
You are given an array start where start = [startX, startY] represents your initial position (startX, startY) in a 2D
space. You are also given the array target where target = [targetX, targetY] represents your target position (targetX,
targetY).

The cost of going from a position (x1, y1) to any other position in the space (x2, y2) is |x2 - x1| + |y2 - y1|.

There are also some special roads. You are given a 2D array specialRoads where specialRoads[i] = [x1i, y1i, x2i, y2i,
costi] indicates that the ith special road goes in one direction from (x1i, y1i) to (x2i, y2i) with a cost equal to
costi. You can use each special road any number of times.

Return the minimum cost required to go from (startX, startY) to (targetX, targetY).



Example 1:

Input: start = [1,1], target = [4,5], specialRoads = [[1,2,3,3,2],[3,4,4,5,1]]

Output: 5

Explanation:

(1,1) to (1,2) with a cost of |1 - 1| + |2 - 1| = 1.
(1,2) to (3,3). Use specialRoads[0] with the cost 2.
(3,3) to (3,4) with a cost of |3 - 3| + |4 - 3| = 1.
(3,4) to (4,5). Use specialRoads[1] with the cost 1.
So the total cost is 1 + 2 + 1 + 1 = 5.

Example 2:

Input: start = [3,2], target = [5,7], specialRoads = [[5,7,3,2,1],[3,2,3,4,4],[3,3,5,5,5],[3,4,5,6,6]]

Output: 7

Explanation:

It is optimal not to use any special edges and go directly from the starting to the ending position with a cost |5 - 3|
+ |7 - 2| = 7.

Note that the specialRoads[0] is directed from (5,7) to (3,2).

Example 3:

Input: start = [1,1], target = [10,4], specialRoads = [[4,2,1,1,3],[1,2,7,4,4],[10,3,6,1,2],[6,1,1,2,3]]

Output: 8

Explanation:

(1,1) to (1,2) with a cost of |1 - 1| + |2 - 1| = 1.
(1,2) to (7,4). Use specialRoads[1] with the cost 4.
(7,4) to (10,4) with a cost of |10 - 7| + |4 - 4| = 3.


Constraints:

start.length == target.length == 2
1 <= startX <= targetX <= 105
1 <= startY <= targetY <= 105
1 <= specialRoads.length <= 200
specialRoads[i].length == 5
startX <= x1i, x2i <= targetX
startY <= y1i, y2i <= targetY
1 <= costi <= 105
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
Intuition
The approach involves using Dijkstra's algorithm to find the minimum cost path from the starting point to the target
point. Initially, we set the distances to all the special roads from the starting point, and push them into a priority
queue with the current distance as the priority. We then start extracting the minimum element from the priority queue
and check if its distance is equal to the distance stored in the vector. If not, we ignore it and continue with the next
element.

We calculate the distance to the target point via the current element and update the answer if it is less than the
current answer. We then iterate over all the special roads and update their distance if it is less than the previously
stored distance. We then push this special road onto the priority queue with the new distance as the priority.

We repeat this process until the priority queue is empty and return the final answer.

Approach
The given problem can be solved using Dijkstra's algorithm. We can think of each special road as a node in the graph and
the weight of each edge as the cost of traveling between the two special roads. To compute the cost of traveling from
start to target, we can first calculate the cost of traveling from the start to each special road and then use these
costs to update the cost of traveling to other special roads. Finally, we can add the cost of traveling from the target
to the special road with minimum total cost.

Specifically, we can first initialize a vector d of distances from the start to each special road. For each special road
i, we can calculate d[i] as the sum of the Manhattan distance between the start and the special road and the cost of the
special road. We can then use a min-heap to store the distances and the indices of the special roads. We can start with
the distances and indices of the special roads as the source and use Dijkstra's algorithm to update the distances and
indices of the special roads. To update the distance of a special road i, we can consider all the special roads that are
connected to it and update their distances if the distance to i plus the weight of the edge connecting i and another
special road is less than their current distances. Finally, we can add the distance from the target to the special road
with minimum total cost to the total cost.

Complexity
Time complexity:
The time complexity of the solution is O(n^2 log n), where n is the number of special roads. The reason for this time
complexity is the loop that iterates over all the special roads and the priority queue operations, which have a time
complexity of O(log n).

Space complexity:
The space complexity of the solution is O(n), which is due to the space occupied by the distance array. The priority
queue takes O(n) space as well. Thus, the overall space complexity is O(n).
 *
The key insight is that you don't need to build a full graph. The only "nodes" that matter are the endpoints of special
roads (plus start and target). Between any two points you can always walk Manhattan distance, but special roads might
offer shortcuts.

Complexity is O(N² log N) where N = number of special roads, since every node tries to relax every other node. That's
fine given the constraint (N ≤ 200).

你原来的方法：从城市 i 跑 Dijkstra，算出 i 到所有城市的最短距离，然后挑 min((k+1)*dist(i,j) + appleCost[j])。对每个 i
都重新跑一遍，N 个起点就是 N 次完整的 Dijkstra。 多源 Dijkstra 快在哪：不同起点的最优解往往共享大量路径。比如城市 3
和城市 5 的最优选择可能都是去城市 8 买苹果，它们到城市 8 的最短路有大量重叠的边。N 次 Dijkstra
会反复探索这些重叠的边，而多源 Dijkstra 只探索一次。 直觉上可以这样理解：想象每个城市 j
同时向外"广播"一个信号，信号强度的初始值是 appleCost[j]，沿边传播时每经过一条边 toll 就增加
(k+1)*toll。所有城市同时广播，每个城市 i 只记录它收到的最小信号值。因为 Dijkstra 按代价从小到大处理，当城市 i
第一次被"定下来"时，它已经找到了全局最优的苹果来源——不需要知道那个苹果具体来自哪个城市。 本质上，N 次单源 Dijkstra
的总工作量是 O(N * E log N)，而多源 Dijkstra 虽然初始队列有 N 个元素，但每条边最多被有效松弛常数次，总工作量还是 O(E log
N)。省掉的就是那个 N 倍

-=-=
那如果我想知道具体从某个 city 出发, 最优应该去哪个 city 买苹果的话, 是不是就还得回到 N 次单源的方式? 能也用多源解决么

4:06 PM
可以用多源解决，只需要多记录一个信息：这个最优信号是从哪个城市发出的。

cpp
// dist[i] = min total cost starting from city i
// source[i] = which city to buy apple from, if starting at city i
vector<long long> dist(n);
vector<int> source(n);

for (int i = 0; i < n; i++) {
    dist[i] = appleCost[i];
    source[i] = i;  // initially, buy apple at your own city
    pq.push({dist[i], i});
}

while (!pq.empty()) {
    auto [cost, cur] = pq.top();
    pq.pop();

    if (cost > dist[cur]) continue;

    for (auto [next, toll] : graph[cur]) {
        long long new_cost = cost + (long long)(k + 1) * toll;
        if (new_cost < dist[next]) {
            dist[next] = new_cost;
            source[next] = source[cur];  // inherit the apple source
            pq.push({new_cost, next});
        }
    }
}
原理很简单：当城市 cur 的信号松弛了城市 next 时，说明 next 的最优方案是"走到 cur，然后用 cur 的最优方案"。而 cur
的最优苹果来源是 source[cur]，所以 next 直接继承就行。

这就像信号传播时带了一个"标签"，标记着这个信号最初是从哪个苹果源发出的。最终 source[i] 就是城市 i
应该去买苹果的最优城市。
*/
class Solution {
public:
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        int n = specialRoads.size();

        vector<int> min_dist(n, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for (int i = 0; i < n; i++) {
            int dist_to_entrance = abs(start[0] - specialRoads[i][0]) + abs(start[1] - specialRoads[i][1]);
            min_dist[i] = dist_to_entrance + specialRoads[i][4];
            pq.push({min_dist[i], i});
        }

        int rst = abs(target[0] - start[0]) + abs(target[1] - start[1]);
        while (!pq.empty()) {
            int cur_dist = pq.top().first;
            int cur = pq.top().second;
            pq.pop();

            if (cur_dist > min_dist[cur]) {
                continue;
            }

            int dist_to_target = abs(target[0] - specialRoads[cur][2]) + abs(target[1] - specialRoads[cur][3]);
            rst = min(rst, dist_to_target + cur_dist);
            for (int nxt = 0; nxt < n; nxt++) {
                if (nxt == cur) {
                    continue;
                }

                int dist_to_next = abs(specialRoads[cur][2] - specialRoads[nxt][0]) +
                                   abs(specialRoads[cur][3] - specialRoads[nxt][1]);
                if (dist_to_next + cur_dist + specialRoads[nxt][4] < min_dist[nxt]) {
                    min_dist[nxt] = dist_to_next + cur_dist + specialRoads[nxt][4];
                    pq.push({min_dist[nxt], nxt});
                }
            }
        }
        return rst;
    }
};
