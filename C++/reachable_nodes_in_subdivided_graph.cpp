/*
 882. Reachable Nodes In Subdivided Graph
 Starting with an undirected graph (the "original graph") with nodes from 0 to N-1, subdivisions are made to some of the edges.

 The graph is given as follows: edges[k] is a list of integer pairs (i, j, n) such that (i, j) is an edge of the original graph,

 and n is the total number of new nodes on that edge.

 Then, the edge (i, j) is deleted from the original graph, n new nodes (x_1, x_2, ..., x_n) are added to the original graph,

 and n+1 new edges (i, x_1), (x_1, x_2), (x_2, x_3), ..., (x_{n-1}, x_n), (x_n, j) are added to the original graph.

 Now, you start at node 0 from the original graph, and in each move, you travel along one edge.

 Return how many nodes you can reach in at most M moves.



 Example 1:

 Input: edges = [[0,1,10],[0,2,1],[1,2,2]], M = 6, N = 3
 Output: 13
 Explanation:
 The nodes that are reachable in the final graph after M = 6 moves are indicated below.

 Example 2:

 Input: edges = [[0,1,4],[1,2,6],[0,2,8],[1,3,1]], M = 10, N = 4
 Output: 23


 Note:

 0 <= edges.length <= 10000
 0 <= edges[i][0] < edges[i][1] < N
 There does not exist any i != j for which edges[i][0] == edges[j][0] and edges[i][1] == edges[j][1].
 The original graph has no parallel edges.
 0 <= edges[i][2] <= 10000
 0 <= M <= 10^9
 1 <= N <= 3000
 A reachable node is a node that can be travelled to using at most M moves starting from node 0.
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
#include <stdio.h>
#include <map>
#include <numeric>
using namespace std;

/*
Intuition:
Store edges to another 2D hashtable e, so that we can easier get length between two node by e[i][j].
seen[i] means that we can arrive at node i and have seen[i] moves left.

We use a dijkstra algorithm in this solution.
Priority queue pq store states (moves left, node index).
So every time when we pop from pq, we get the state with the most moves left.

In the end, we calculate the number of nodes that we can reach.

res = seen.length
For every edge e[i][j]:
res += min(seen.getOrDefault(i, 0) + seen.getOrDefault(j, 0), e[i][j])

Time Complexity:
Reminded by @kAc:
Dijkstra + Heap is O(E log E)
Dijkstra + Fibonacci heap is O(N log N + E)
*/
class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int M, int N) {
        unordered_map<int, unordered_map<int, int>> distance;
        for (vector<int>& edge : edges) {
            distance[edge[0]][edge[1]] = edge[2];
            distance[edge[1]][edge[0]] = edge[2];
        }

        priority_queue<pair<int, int>> pq;
        pq.push({M, 0});
        unordered_map<int, int> seen;
        while (!pq.empty()) {
            int moves = pq.top().first;
            int cur = pq.top().second;
            pq.pop();

            if (seen.find(cur) == seen.end()) {
                seen[cur] = moves;
                for (auto& next : distance[cur]) {
                    int leftMoves = moves - next.second - 1;
                    if (seen.find(next.first) == seen.end() and leftMoves >= 0) {
                        pq.push({leftMoves, next.first});
                    }
                }
            }
        }

        int result = seen.size();
        for (vector<int>& edge : edges) {
            int a = seen.find(edge[0]) == seen.end() ? 0 : seen[edge[0]];
            int b = seen.find(edge[1]) == seen.end() ? 0 : seen[edge[1]];
            result += min(a + b, edge[2]);
        }
        return result;
    }
};

class Solution1 { // 5.06%
public:
    int reachableNodes(vector<vector<int>> edges, int M, int N) {
        unordered_map<int, vector<int>> next;
        unordered_map<int, unordered_map<int, int>> distance;
        unordered_map<int, unordered_map<int, int>> used;
        for (vector<int>& edge : edges) {
            int start = edge[0];
            int end = edge[1];
            next[start].push_back(end);
            next[end].push_back(start);
            distance[start][end] = edge[2];
            distance[end][start] = edge[2];
            used[start][end] = 0;
            used[end][start] = 0;
        }

        unordered_map<int, int> visited;
        queue<pair<int, int>> bfs;
        bfs.push({0, M});
        visited[0] = M;
        while (!bfs.empty()) {
            int cur = bfs.front().first;
            int leftMove = bfs.front().second;
            bfs.pop();

            for (int node : next[cur]) {
                if (leftMove >= distance[cur][node] + 1) {
                    used[cur][node] = distance[cur][node];
                    if (leftMove - distance[cur][node] - 1 > visited[node]) {
                        bfs.push({node, leftMove - distance[cur][node] - 1});
                        visited[node] = leftMove - distance[cur][node] - 1;
                    }
                }
                else {
                    if (leftMove > used[cur][node]) {
                        used[cur][node] = leftMove;
                    }
                }
            }
        }

        int usedNodes = 0;
        for (auto it = used.begin(); it != used.end(); it++) {
            int start = it -> first;
            unordered_map<int, int> usage = it -> second;
            for (auto it2 = usage.begin(); it2 != usage.end(); it2++) {
                int end = it2 -> first;
                usedNodes += min(distance[start][end], it2 -> second + used[end][start]);
                used[start][end] = 0;
                used[end][start] = 0;
            }
        }
        return usedNodes + visited.size();
    }
};
