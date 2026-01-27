/*
https://leetcode.com/problems/distance-to-a-cycle-in-undirected-graph/description/
2204. Distance to a Cycle in Undirected Graph

You are given a positive integer n representing the number of nodes in a connected undirected graph containing exactly
one cycle. The nodes are numbered from 0 to n - 1 (inclusive).

You are also given a 2D integer array edges, where edges[i] = [node1i, node2i] denotes that there is a bidirectional
edge connecting node1i and node2i in the graph.

The distance between two nodes a and b is defined to be the minimum number of edges that are needed to go from a to b.

Return an integer array answer of size n, where answer[i] is the minimum distance between the ith node and any node in
the cycle.



Example 1:


Input: n = 7, edges = [[1,2],[2,4],[4,3],[3,1],[0,1],[5,2],[6,5]]
Output: [1,0,0,0,0,1,2]
Explanation:
The nodes 1, 2, 3, and 4 form the cycle.
The distance from 0 to 1 is 1.
The distance from 1 to 1 is 0.
The distance from 2 to 2 is 0.
The distance from 3 to 3 is 0.
The distance from 4 to 4 is 0.
The distance from 5 to 2 is 1.
The distance from 6 to 2 is 2.
Example 2:


Input: n = 9, edges = [[0,1],[1,2],[0,2],[2,6],[6,7],[6,8],[0,3],[3,4],[3,5]]
Output: [0,0,0,1,2,2,1,2,2]
Explanation:
The nodes 0, 1, and 2 form the cycle.
The distance from 0 to 0 is 0.
The distance from 1 to 1 is 0.
The distance from 2 to 2 is 0.
The distance from 3 to 1 is 1.
The distance from 4 to 1 is 2.
The distance from 5 to 1 is 2.
The distance from 6 to 2 is 1.
The distance from 7 to 2 is 2.
The distance from 8 to 2 is 2.


Constraints:

3 <= n <= 105
edges.length == n
edges[i].length == 2
0 <= node1i, node2i <= n - 1
node1i != node2i
The graph is connected.
The graph has exactly one cycle.
There is at most one edge between any pair of vertices.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
#include <numeric>
using namespace std;

/*
Idea:
1) Find which nodes are in a cycle (remove nodes using onion peeling)
we can use both DFS or BFS
// DFS to detect cycle nodes and mark them in `isInCycle`
    bool detectCycleNodes(int currentNode, vector<vector<int>> &adjacencyList,
                          vector<bool> &isInCycle, vector<bool> &visited,
                          vector<int> &parent) {
        visited[currentNode] = true;  // Mark current node as visited
        for (auto neighbor : adjacencyList[currentNode]) {
            if (!visited[neighbor]) {
                parent[neighbor] = currentNode;  // Set parent for backtracking
                if (detectCycleNodes(neighbor, adjacencyList, isInCycle,
                                     visited, parent))
                    return true;  // Return true if cycle detected
            } else if (parent[currentNode] != neighbor) {  // Cycle detected
                isInCycle[neighbor] = true;  // Mark the start of the cycle
                int tempNode = currentNode;
                // Backtrack to mark all nodes in the cycle
                while (tempNode != neighbor) {
                    isInCycle[tempNode] = true;
                    tempNode = parent[tempNode];
                }
                return true;
            }
        }
        return false;  // No cycle found in this path
    }
2) Add those nodes in cycle to a queue and use BFS to find distance of each node to any node in cycle
*/
class Solution {
public:
    vector<int> distanceToCycle(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n, vector<int>());
        vector<int> degree(n, 0);
        for (vector<int> e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
            degree[e[0]] += 1;
            degree[e[1]] += 1;
        }

        // BFS to find all cycle nodes
        queue<int> bfs;
        vector<bool> visited(n, false);
        for (int i = 0; i < n; i++) {
            if (degree[i] == 1) {
                bfs.push(i);
                visited[i] = true;
            }
        }

        while (!bfs.empty()) {
            int cur = bfs.front();
            bfs.pop();

            for (int neighbour : adj[cur]) {
                if (visited[neighbour]) {
                    continue;
                }

                degree[neighbour] -= 1;
                if (degree[neighbour] == 1) {
                    bfs.push(neighbour);
                    visited[neighbour] = true;
                }
            }
        }

        // BFS to find the shortest distance for cycle nodes to other nodes
        vector<int> rst(n, INT_MAX);
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                bfs.push(i);
                rst[i] = 0;
            }
        }

        int cur_dist = 0;
        while (!bfs.empty()) {
            int cur_size = bfs.size();
            for (int i = 0; i < cur_size; i++) {
                int cur = bfs.front();
                bfs.pop();

                for (int neighbour : adj[cur]) {
                    if (rst[neighbour] > cur_dist + 1) {
                        rst[neighbour] = cur_dist + 1;
                        bfs.push(neighbour);
                    }
                }
            }
            cur_dist += 1;
        }
        return rst;
    }
};