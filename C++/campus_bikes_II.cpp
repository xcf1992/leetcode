/*
 1066. Campus Bikes II
 On a campus represented as a 2D grid, there are N workers and M bikes, with N <= M.
 Each worker and bike is a 2D coordinate on this grid.

 We assign one unique bike to each worker
 so that the sum of the Manhattan distances between each worker and their assigned bike is minimized.

 The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|.

 Return the minimum possible sum of Manhattan distances between each worker and their assigned bike.

 Example 1:

 Input: workers = [[0,0],[2,1]], bikes = [[1,2],[3,3]]
 Output: 6
 Explanation:
 We assign bike 0 to worker 0, bike 1 to worker 1. The Manhattan distance of both assignments is 3, so the output is 6.
 Example 2:



 Input: workers = [[0,0],[1,1],[2,0]], bikes = [[1,0],[2,2],[2,1]]
 Output: 4
 Explanation:
 We first assign bike 0 to worker 0, then assign bike 1 to worker 1 or worker 2,
 bike 2 to worker 2 or worker 1. Both assignments lead to sum of the Manhattan distances as 4.


 Note:

 0 <= workers[i][0], workers[i][1], bikes[i][0], bikes[i][1] < 1000
 All worker and bike locations are distinct.
 1 <= workers.length <= bikes.length <= 10
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

class Solution { // dfs with memo, use vector as memo, much faster than map from 50ms ~ 12ms
private:
    int M = 0;
    int N = 0;

    int getDistance(vector<int>& worker, vector<int>& bike) {
        return abs(worker[0] - bike[0]) + abs(worker[1] - bike[1]);
    }

    int dfs(vector<vector<int>>& workers, vector<vector<int>>& bikes, vector<vector<int>>& memo, int curWorker, int occupied) {
        if (curWorker >= N) {
            return 0;
        }

        if (memo[occupied][curWorker] != INT_MAX) {
            return memo[occupied][curWorker];
        }

        for (int i = 0; i < M; ++i) if ((occupied & (1 << i)) == 0) { // this bike is not taken by anyone
            int temp = getDistance(workers[curWorker], bikes[i]) + dfs(workers, bikes, memo, curWorker + 1, (occupied | (1 << i)));
            memo[occupied][curWorker] = min(memo[occupied][curWorker], temp);
        }
        return memo[occupied][curWorker];
    }
public:
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        M = bikes.size();
        N = workers.size();
        vector<vector<int>> memo(1 << M, vector<int>(N, INT_MAX));
        return dfs(workers, bikes, memo, 0, 0);
    }
};

class Solution { // dfs with memo
private:
    unordered_map<string, int> memo;
    int M = 0;
    int N = 0;

    int getDistance(vector<int>& worker, vector<int>& bike) {
        return abs(worker[0] - bike[0]) + abs(worker[1] - bike[1]);
    }

    int dfs(vector<vector<int>>& workers, vector<vector<int>>& bikes, int curWorker, int occupied) {
        if (curWorker >= N) {
            return 0;
        }

        string key = to_string(curWorker) + "_" + to_string(occupied);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }

        memo[key] = INT_MAX;
        for (int i = 0; i < M; ++i) if ((occupied & (1 << i)) == 0) { // this bike is not taken by anyone
            int temp = getDistance(workers[curWorker], bikes[i]) + dfs(workers, bikes, curWorker + 1, (occupied | (1 << i)));
            memo[key] = min(memo[key], temp);
        }
        return memo[key];
    }
public:
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        M = bikes.size();
        N = workers.size();
        return dfs(workers, bikes, 0, 0);
    }
};

// naive dfs TLE
class Solution1 {
private:
    int result = INT_MAX;

    void dfs(vector<vector<int>>& workers, int i, vector<vector<int>>& bikes, vector<bool>& used, int sum) {
        if (i == workers.size()) {
            result = min(result, sum);
            return;
        }

        if (sum > result) {
            return;  // early termination
        }

        for (int j = 0; j < bikes.size(); ++j) {
            if (used[j]) continue;
            used[j] = true;
            dfs(workers, i + 1, bikes, used, sum + getDistance(workers[i], bikes[j]));
            used[j] = false;
        }
    }

    int getDistance(vector<int>& worker, vector<int>& bike) {
        return abs(worker[0] - bike[0]) + abs(worker[1] - bike[1]);
    }
public:
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        vector<bool> used(bikes.size(), false);
        dfs(workers, 0, bikes, used, 0);
        return result;
    }
};
