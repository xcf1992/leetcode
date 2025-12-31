/*
https://leetcode.com/problems/find-the-closest-marked-node/description/
2737. Find the Closest Marked Node

You are given a positive integer n which is the number of nodes of a 0-indexed directed weighted graph and a 0-indexed
2D array edges where edges[i] = [ui, vi, wi] indicates that there is an edge from node ui to node vi with weight wi.

You are also given a node s and a node array marked; your task is to find the minimum distance from s to any of the
nodes in marked.

Return an integer denoting the minimum distance from s to any node in marked or -1 if there are no paths from s to any
of the marked nodes.



Example 1:

Input: n = 4, edges = [[0,1,1],[1,2,3],[2,3,2],[0,3,4]], s = 0, marked = [2,3]
Output: 4
Explanation: There is one path from node 0 (the green node) to node 2 (a red node), which is 0->1->2, and has a distance
of 1 + 3 = 4. There are two paths from node 0 to node 3 (a red node), which are 0->1->2->3 and 0->3, the first one has a
distance of 1 + 3 + 2 = 6 and the second one has a distance of 4. The minimum of them is 4.


Example 2:

Input: n = 5, edges = [[0,1,2],[0,2,4],[1,3,1],[2,3,3],[3,4,2]], s = 1, marked = [0,4]
Output: 3
Explanation: There are no paths from node 1 (the green node) to node 0 (a red node).
There is one path from node 1 to node 4 (a red node), which is 1->3->4, and has a distance of 1 + 2 = 3.
So the answer is 3.


Example 3:

Input: n = 4, edges = [[0,1,1],[1,2,3],[2,3,2]], s = 3, marked = [0,1]
Output: -1
Explanation: There are no paths from node 3 (the green node) to any of the marked nodes (the red nodes), so the answer
is -1.




Constraints:

2 <= n <= 500
1 <= edges.length <= 104
edges[i].length = 3
0 <= edges[i][0], edges[i][1] <= n - 1
1 <= edges[i][2] <= 106
1 <= marked.length <= n - 1
0 <= s, marked[i] <= n - 1
s != marked[i]
marked[i] != marked[j] for every i != j
The graph might have repeated edges.
The graph is generated such that it has no self-loops.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

class Solution {
public:
    int minimumDistance(int n, vector<vector<int>>& edges, int s, vector<int>& marked) {
        vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>>());
        for (vector<int> e : edges) {
            graph[e[0]].push_back({e[1], e[2]});
        }

        vector<int> min_distance(n, INT_MAX);
        min_distance[s] = 0;

        queue<pair<int, int>> bfs;
        bfs.push({s, 0});
        while (!bfs.empty()) {
            int cur = bfs.front().first;
            int dist = bfs.front().second;
            bfs.pop();

            for (auto& [next, weight] : graph[cur]) {
                if (weight + dist < min_distance[next]) {
                    min_distance[next] = dist + weight;
                    bfs.push({next, min_distance[next]});
                }
            }
        }

        int rst = INT_MAX;
        for (int i : marked) {
            rst = min(rst, min_distance[i]);
        }
        return rst == INT_MAX ? -1 : rst;
    }
};

class Solution {
public:
    int minimumDistance(int n, vector<vector<int>>& edges, int s, vector<int>& marked) {
        // Convert marked array to set for O(1) lookups
        unordered_set<int> markSet(marked.begin(), marked.end());

        // Build adjacency list representation of the graph
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].emplace_back(edge[1], edge[2]);
        }

        // Initialize distance array with infinity values
        vector<int> dist(n, INT_MAX);
        dist[s] = 0;

        // Min heap prioritized by distance
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
        minHeap.emplace(0, s);

        // Dijkstra's algorithm
        while (!minHeap.empty()) {
            auto [distance, node] = minHeap.top();
            minHeap.pop();

            // Found a marked node, return its distance
            if (markSet.count(node)) {
                return dist[node];
            }

            // Explore neighbors
            for (const auto& [nextNode, weight] : adj[node]) {
                int newDist = distance + weight;

                // If we found a shorter path, update and add to the priority
                // queue
                if (newDist < dist[nextNode]) {
                    dist[nextNode] = newDist;
                    minHeap.emplace(newDist, nextNode);
                }
            }
        }

        // No path found to any marked node
        return -1;
    }
};

/*
Intuition
Dijkstra’s Algorithm is a great choice for finding shortest paths in graphs with non-negative edge weights, but it fails
when negative weights are involved. The Bellman-Ford Algorithm, on the other hand, is designed to handle graphs with
negative weights, making it more general. While we don't have negative weights in this problem, understanding
Bellman-Ford helps us see an alternative approach that works under broader conditions.

The core idea behind Bellman-Ford is straightforward: in a graph with n nodes, the shortest path between any two nodes
can have at most n - 1 edges. If a path has n or more edges, it must contain a cycle. Since we're only interested in
simple paths (paths without cycles), we never need more than n - 1 edges to reach any node optimally.

Now, let’s apply this to our problem. We start at node s and want to determine the shortest path to any node in the
marked array. Instead of immediately finding the best path, Bellman-Ford gradually refines our understanding of
distances by repeatedly considering all edges in the graph.

To implement this approach, we first initialize an array dist, where dist[i] represents the shortest known distance from
s to node i. Initially, all values are set to infinity (or a very large number), except for s, which starts at 0 since
it takes no cost to reach itself. This setup reflects our initial knowledge: we know how to reach s but have no
information about the shortest paths to other nodes.

The algorithm’s core operation is edge relaxation. This means checking every edge (u, v, weight) in the graph and
updating dist[v] if we find a shorter path to v through u. If dist[u] + weight < dist[v], we update dist[v]. This
process is repeated exactly n - 1 times because, in the worst case, the shortest path to any node may require n - 1
edges.

Why n - 1 iterations? The first pass ensures that we find the shortest one-edge paths. The second pass builds on that,
discovering the shortest two-edge paths, and so on. By the time we've repeated this process n - 1 times, all shortest
paths have been fully propagated throughout the graph.

Here's a slideshow to demonstrate how the dist array is filled between each relaxation loop:
 */
class Solution {
public:
    int minimumDistance(int n, vector<vector<int>>& edges, int s, vector<int>& marked) {
        // Initialize distances array with maximum values
        vector<int> dist(n, INT_MAX);
        dist[s] = 0;

        // Bellman-Ford algorithm: relax edges n-1 times
        for (int iter = 0; iter < n - 1; iter++) {
            for (const auto& edge : edges) {
                int from = edge[0];
                int to = edge[1];
                int weight = edge[2];

                // Relaxation step: if we can improve the path to 'to' via
                // 'from'
                if (dist[from] != INT_MAX && dist[from] + weight < dist[to]) {
                    dist[to] = dist[from] + weight;
                }
            }
        }

        // Find minimum distance to any marked node
        int minDist = INT_MAX;
        for (int node : marked) {
            if (dist[node] < minDist) {
                minDist = dist[node];
            }
        }

        // Return -1 if no path exists, otherwise return the minimum distance
        return minDist == INT_MAX ? -1 : minDist;
    }
};

/*
Intuition
Now, let's explore a lesser-known but powerful algorithm called the Shortest Path Faster Algorithm (SPFA). This
algorithm is an optimization of Bellman-Ford and combines ideas from both Bellman-Ford and Breadth-First Search (BFS) to
achieve better performance in many cases.

To understand SPFA, let’s consider why Bellman-Ford can be inefficient. When relaxing edges in the Bellman-Ford
algorithm, many iterations might not lead to any improvements in the distance values. SPFA addresses this inefficiency
by only considering nodes whose distances have been updated recently, as only these nodes have the potential to update
their neighbors.

Think of it like a road network: if the estimated travel time to a city changes, it might affect nearby cities but not
those farther away. SPFA follows this natural flow of information by recalculating routes only through cities whose
travel times have changed.

The key idea behind SPFA is that a node’s outgoing edges need to be checked only if its shortest known distance has been
updated. To achieve this, SPFA maintains a queue of "active" nodes i.e., nodes that have recently had their shortest
distances improved. When we improve the distance to a node, we add it to the queue (if it's not already there). Then, we
process the queue by repeatedly:

Removing a node from the queue.
Exploring all its outgoing edges, potentially updating distances to neighbors.
Adding any neighbor whose distance was improved to the queue.
Along with the queue and the distance array used in the Bellman-Ford Algorithm, SPFA also maintains a boolean array to
track which nodes are currently in the queue. During relaxation, we only add nodes that are not currently enqueued to
prevent duplicate entries.

Once the queue is empty, the shortest paths from the source to all reachable nodes have been found. The final step is to
check the distances of all marked nodes and return the smallest among them.

What makes SPFA particularly useful is that it adapts to the structure of the graph. In sparse graphs or graphs where
the shortest paths are discovered quickly, SPFA can be significantly faster than the standard Bellman-Ford algorithm.
However, it's worth noting that SPFA doesn't improve the worst-case time complexity – in worst-case scenarios, a node
might enter the queue multiple times, potentially up to the number of edges in the graph.

For a more comprehensive understanding of various graph algorithms like Dijkstra's, Bellman-Ford, and SPFA, check out
the Graph Explore Card. This resource provides an in-depth look at popular graph algorithms, explaining their key
concepts and applications with a variety of problems to solidify understanding of the pattern.

Algorithm
Initialize a list of lists of pairs called graph to represent the adjacency list.
Build the graph by iterating through each edge in the edges list:
Extract the source node (from), the destination node (to), and the weight.
Add an array containing the destination node and weight to the source node's adjacency list.
Initialize an integer array dist of size n to track distances from the source.
Fill the dist array with infinity.
Set the distance to the starting node s as 0.
Initialize a queue to implement the SPFA algorithm.
Add the source node s to the queue.
Initialize a boolean array inQueue of size n to track which nodes are currently in the queue.
Mark the source node as being in the queue.
While the queue is not empty:
Remove the front node from the queue and store it in current.
Mark the current node as no longer in the queue.
For each neighbor of current:
Extract the nextNode and the weight of the edge.
Perform the relaxation step: if we can improve the path to the neighbor via the current node, update the distance.
If the neighbor is not already in the queue, add it and mark it as being in the queue.
Initialize a variable minDist to infinity to track the minimum distance to any marked node.
For each node in the marked array:
Update minDist to be the minimum of its current value and the distance to this marked node.
Return -1 if no path exists (minDist is still infinity), otherwise return the minimum distance.
 */

class Solution {
public:
    int minimumDistance(int n, vector<vector<int>>& edges, int s,
                        vector<int>& marked) {
        // Adjacency list representation
        vector<vector<pair<int, int>>> graph(n);

        // Build the graph
        for (const auto& edge : edges) {
            int from = edge[0], to = edge[1], weight = edge[2];
            graph[from].emplace_back(to, weight);
        }

        // Distance array
        vector<int> dist(n, INT_MAX);
        dist[s] = 0;

        queue<int> queue;
        queue.push(s);

        // Track nodes in queue
        vector<bool> inQueue(n, false);
        inQueue[s] = true;

        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();
            inQueue[current] = false;

            // Explore neighbors
            for (const auto& [nextNode, weight] : graph[current]) {
                // Relaxation step
                if (dist[nextNode] > dist[current] + weight) {
                    dist[nextNode] = dist[current] + weight;

                    // Add to queue if not already in queue
                    if (!inQueue[nextNode]) {
                        queue.push(nextNode);
                        inQueue[nextNode] = true;
                    }
                }
            }
        }

        // Find minimum distance to any marked node
        int minDist = INT_MAX;
        for (int node : marked) {
            minDist = min(minDist, dist[node]);
        }

        return minDist == INT_MAX ? -1 : minDist;
    }
};