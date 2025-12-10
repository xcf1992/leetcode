/*
1617. Count Subtrees With Max Distance Between Cities
https://leetcode.com/problems/count-subtrees-with-max-distance-between-cities/

There are n cities numbered from 1 to n. You are given an array edges of size n-1,
where edges[i] = [ui, vi] represents a bidirectional edge between cities ui and vi.
There exists a unique path between each pair of cities. In other words, the cities form a tree.

A subtree is a subset of cities where every city is reachable from every other city in the subset,
where the path between each pair passes through only the cities from the subset.
Two subtrees are different if there is a city in one subtree that is not present in the other.

For each d from 1 to n-1, find the number of subtrees
in which the maximum distance between any two cities in the subtree is equal to d.

Return an array of size n-1 where the dth element (1-indexed) is the number of subtrees
in which the maximum distance between any two cities is equal to d.

Notice that the distance between the two cities is the number of edges in the path between them.

Example 1:
Input: n = 4, edges = [[1,2],[2,3],[2,4]]
Output: [3,4,0]
Explanation:
The subtrees with subsets {1,2}, {2,3} and {2,4} have a max distance of 1.
The subtrees with subsets {1,2,3}, {1,2,4}, {2,3,4} and {1,2,3,4} have a max distance of 2.
No subtree has two nodes where the max distance between them is 3.

Example 2:
Input: n = 2, edges = [[1,2]]
Output: [1]

Example 3:
Input: n = 3, edges = [[1,2],[2,3]]
Output: [2,1]

Constraints:
2 <= n <= 15
edges.length == n-1
edges[i].length == 2
1 <= ui, vi <= n
All pairs (ui, vi) are distinct.
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
#include <cfloat>
#include <climits>
#include <map>

using namespace std;
/*
Using Floyd-Warshall algorithm to calculate minimum distance between any node to any other node.
Since n <= 15, there is a maximum 2^15 subset of cities numbered from 1 to n.
For each of subset of cities:
Our subset forms a subtree if and only if number of edges = number of cities - 1
Iterate all pair of cities to calculate number of edges, number of cities, maximum distance between any 2 cities
Complexity

Time: O(2^n * n^2)
Space: O(n^2)
*/
class Solution {
private:
    int maxDistance(int state, vector<vector<int>>& dist, int n) {
        int cntEdge = 0, cntCity = 0, maxDist = 0;
        for (int i = 0; i < n; i++) {
            if (((state >> i) & 1) == 0) {
                continue;  // Skip if city `i` not in our subset
            }

            cntCity += 1;
            for (int j = i + 1; j < n; j++) {
                if (((state >> j) & 1) == 0) {
                    continue;  // Skip if city `j` not in our subset
                }

                cntEdge += dist[i][j] == 1;
                maxDist = max(maxDist, dist[i][j]);
            }
        }
        if (cntEdge != cntCity - 1) {
            return 0;  // Subset form an invalid subtree!
        }
        return maxDist;
    }

public:
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        int INF = n;  // Since cities form a tree so maximum distance between 2 cities always < n
        vector<vector<int>> dist(n, vector<int>(n, INF));
        for (auto& e : edges) {
            dist[e[0] - 1][e[1] - 1] = dist[e[1] - 1][e[0] - 1] = 1;
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }  // get min distance between any two cities

        vector<int> ans(n - 1, 0);
        for (int state = 0; state < (1 << n); state++) {
            int d = maxDistance(state, dist, n);
            if (d > 0) {
                ans[d - 1] += 1;
            }
        }
        return ans;
    }
};
