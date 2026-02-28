/*
https://leetcode.com/problems/design-graph-with-shortest-path-calculator/description/
2642. Design Graph With Shortest Path Calculator

There is a directed weighted graph that consists of n nodes numbered from 0 to n - 1. The edges of the graph are
initially represented by the given array edges where edges[i] = [fromi, toi, edgeCosti] meaning that there is an edge
from fromi to toi with the cost edgeCosti.

Implement the Graph class:

Graph(int n, int[][] edges) initializes the object with n nodes and the given edges.
addEdge(int[] edge) adds an edge to the list of edges where edge = [from, to, edgeCost]. It is guaranteed that there is
no edge between the two nodes before adding this one. int shortestPath(int node1, int node2) returns the minimum cost of
a path from node1 to node2. If no path exists, return -1. The cost of a path is the sum of the costs of the edges in the
path.


Example 1:


Input
["Graph", "shortestPath", "shortestPath", "addEdge", "shortestPath"]
[[4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]], [3, 2], [0, 3], [[1, 3, 4]], [0, 3]]
Output
[null, 6, -1, null, 6]

Explanation
Graph g = new Graph(4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]);
g.shortestPath(3, 2); // return 6. The shortest path from 3 to 2 in the first diagram above is 3 -> 0 -> 1 -> 2 with a
total cost of 3 + 2 + 1 = 6. g.shortestPath(0, 3); // return -1. There is no path from 0 to 3. g.addEdge([1, 3, 4]); //
We add an edge from node 1 to node 3, and we get the second diagram above. g.shortestPath(0, 3); // return 6. The
shortest path from 0 to 3 now is 0 -> 1 -> 3 with a total cost of 2 + 4 = 6.


Constraints:

1 <= n <= 100
0 <= edges.length <= n * (n - 1)
edges[i].length == edge.length == 3
0 <= fromi, toi, from, to, node1, node2 <= n - 1
1 <= edgeCosti, edgeCost <= 106
There are no repeated edges and no self-loops in the graph at any point.
At most 100 calls will be made for addEdge.
At most 100 calls will be made for shortestPath.
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
using namespace std;

class Graph {
public:
    vector<vector<pair<int, int>>> adj_;

    Graph(int n, vector<vector<int>>& edges) {
        adj_.resize(n);
        for (auto& e: edges) {
            adj_[e[0]].push_back(make_pair(e[1], e[2]));
        }
    }

    void addEdge(vector<int> edge) {
        adj_[edge[0]].push_back(make_pair(edge[1], edge[2]));
    }

    int shortestPath(int node1, int node2) { // time O(ElogV)
        int n = adj_.size();

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        pq.push({0, node1}); // cur_cost, cur_node

        vector<int> min_cost(n, INT_MAX);
        min_cost[node1] = 0;

        while (!pq.empty()) {
            int cur_cost = pq.top()[0];
            int cur_node = pq.top()[1];
            pq.pop();

            if (cur_cost > min_cost[cur_node]) {
                continue;
            }

            if (cur_node == node2) {
                return cur_cost;
            }

            for (auto& neighbor : adj_[cur_node]) {
                int next_node = neighbor.first;
                int cost = neighbor.second;
                int next_cost = cur_cost + cost;
                if (next_cost < min_cost[next_node]) {
                    min_cost[next_node] = next_cost;
                    pq.push({next_cost, next_node});
                }
            }
        }
        return -1;
    }
};
