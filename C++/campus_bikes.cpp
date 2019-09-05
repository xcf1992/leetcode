/*
 1057. Campus Bikes

 On a campus represented as a 2D grid,
 there are N workers and M bikes, with N <= M.
 Each worker and bike is a 2D coordinate on this grid.

 Our goal is to assign a bike to each worker.
 Among the available bikes and workers,
 we choose the (worker, bike) pair with the shortest Manhattan distance between each other,
 and assign the bike to that worker.
 (If there are multiple (worker, bike) pairs with the same shortest Manhattan distance,
 we choose the pair with the smallest worker index;
 if there are multiple ways to do that, we choose the pair with the smallest bike index).
 We repeat this process until there are no available workers.

 The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|.

 Return a vector ans of length N, where ans[i] is the index (0-indexed) of the bike that the i-th worker is assigned to.



 Example 1:



 Input: workers = [[0,0],[2,1]], bikes = [[1,2],[3,3]]
 Output: [1,0]
 Explanation:
 Worker 1 grabs Bike 0 as they are closest (without ties), and Worker 0 is assigned Bike 1. So the output is [1, 0].
 Example 2:



 Input: workers = [[0,0],[1,1],[2,0]], bikes = [[1,0],[2,2],[2,1]]
 Output: [0,2,1]
 Explanation:
 Worker 0 grabs Bike 0 at first. Worker 1 and Worker 2 share the same distance to Bike 2, thus Worker 1 is assigned to Bike 2, and Worker 2 will take Bike 1. So the output is [0,2,1].


 Note:

 0 <= workers[i][j], bikes[i][j] < 1000
 All worker and bike locations are distinct.
 1 <= workers.length <= bikes.length <= 1000
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int n = workers.size();
        int m = bikes.size();

        vector<vector<int>> distance; // worker, bike, distance
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                distance.push_back({i, j, abs(workers[i][0] - bikes[j][0]) + abs(workers[i][1] - bikes[j][1])});
            }
        }
        sort(distance.begin(), distance.end(), [](vector<int>& a, vector<int>& b) {
            return a[2] < b[2]
                or (a[2] == b[2] and a[0] < b[0])
                or (a[2] == b[2] and a[0] == b[0] and a[1] < b[1]);
        });

        vector<int> result(n, -1);
        unordered_set<int> assigned;
        for (vector<int>& dis : distance) {
            if (result[dis[0]] == -1 and assigned.find(dis[1]) == assigned.end()) {
                result[dis[0]] = dis[1];
                assigned.insert(dis[1]);
            }
        }
        return result;
    }
};
