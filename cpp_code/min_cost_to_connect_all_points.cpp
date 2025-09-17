/*
1584. Min Cost to Connect All Points
https://leetcode.com/problems/min-cost-to-connect-all-points/

You are given an array points representing integer coordinates of some points on a 2D-plane,
where points[i] = [xi, yi].

The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them:
|xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.

Return the minimum cost to make all points connected.
All points are connected if there is exactly one simple path between any two points.

Example 1:
Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
Output: 20
Explanation:
We can connect the points as shown above to get the minimum cost of 20.
Notice that there is a unique path between every pair of points.

Example 2:
Input: points = [[3,12],[-2,5],[-4,1]]
Output: 18

Example 3:
Input: points = [[0,0],[1,1],[1,0],[-1,1]]
Output: 4

Example 4:
Input: points = [[-1000000,-1000000],[1000000,1000000]]
Output: 4000000

Example 5:
Input: points = [[0,0]]
Output: 0

Constraints:
1 <= points.length <= 1000
-106 <= xi, yi <= 106
All pairs (xi, yi) are distinct.
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
#include <stdio.h>
#include <map>
using namespace std;
/*
We can imagine that every point is a node of the graph, connected to all other points, and the lenght of the edge is the manhattan distance between two points.

To find the min cost, we therefore need to find the minimum spanning tree.

Note: I tried to sort all edges first, but I got TLE during the contest. I think that limits for C++ are too tight. I then used a min heap, and it worked.

The complexity when using sort is O(n * n log (n * n)) - we have n * n edges. Using a min heap is O(k log (n * n)), where k is the number of edges we need to pull to complete the tree. It's much smaller than n * n in the average case.

We can use the Kruskal algorithm, which involves min heap to pick the smallest edge, and union-find to check if the edge is redundant.

We exit when all points are connected.
*/
class Solution {
public:
int find(vector<int> &ds, int i) {
    return ds[i] < 0 ? i : ds[i] = find(ds, ds[i]);
}
int minCostConnectPoints(vector<vector<int>>& ps) {
    int n = ps.size(), res = 0;
    vector<int> ds(n, -1);
    vector<array<int, 3>> arr;
    for (auto i = 0; i < n; ++i)
        for (auto j = i + 1; j < n; ++j) {
            arr.push_back({abs(ps[i][0] - ps[j][0]) + abs(ps[i][1] - ps[j][1]), i, j});
        }
    make_heap(begin(arr), end(arr), greater<array<int, 3>>());
    while (!arr.empty()) {
        pop_heap(begin(arr), end(arr), greater<array<int, 3>>());
        auto [dist, i, j] = arr.back();
        arr.pop_back();
        i = find(ds, i), j = find(ds, j);
        if (i != j) {
            res += dist;
            ds[i] += ds[j];
            ds[j] = i;
            if (ds[i] == -n)
                break;
        }
    }
    return res;
}
};
