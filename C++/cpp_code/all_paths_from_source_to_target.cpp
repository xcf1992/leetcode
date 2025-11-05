/*
797. All Paths From Source to Target
https://leetcode.com/problems/all-paths-from-source-to-target/

Given a directed, acyclic graph of N nodes.
Find all possible paths from node 0 to node N-1, and return them in any order.

The graph is given as follows:
the nodes are 0, 1, ..., graph.length - 1.
graph[i] is a list of all nodes j for which the edge (i, j) exists.

Example:
Input: [[1,2], [3], [3], []]
Output: [[0,1,3],[0,2,3]]
Explanation: The graph looks like this:
0--->1
|    |
v    v
2--->3
There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.

Note:
The number of nodes in the graph will be in the range [2, 15].
You can print different paths in any order, but you should keep the order of nodes inside one path.
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
using namespace std;

class Solution {
    // dfs with memo, it is actually slower than pure dfs, I believe the cause is we have to insert at the begin of each path
private:
    int N = 0;
    unordered_map<int, vector<vector<int> > > memo;

    vector<vector<int> > dfs(int cur, vector<vector<int> > &graph) {
        if (cur == N - 1) {
            return {{cur}};
        }

        if (memo.find(cur) != memo.end()) {
            return memo[cur];
        }

        for (int next: graph[cur]) {
            for (vector<int> &path: dfs(next, graph)) {
                path.push_back(cur);
                memo[cur].push_back(path);
            }
        }
        return memo[cur];
    }

public:
    vector<vector<int> > allPathsSourceTarget(vector<vector<int> > &graph) {
        N = graph.size();
        vector<vector<int> > result = dfs(0, graph);
        for (vector<int> &path: result) {
            reverse(path.begin(), path.end());
        }
        return result;
    }
};

class Solution1 {
private:
    int N = 0;

    void dfs(int cur, vector<int> &path, vector<vector<int> > &result, vector<vector<int> > &graph) {
        if (cur == N - 1) {
            result.push_back(path);
            return;
        }

        for (int next: graph[cur]) {
            path.push_back(next);
            dfs(next, path, result, graph);
            path.pop_back();
        }
    }

public:
    vector<vector<int> > allPathsSourceTarget(vector<vector<int> > &graph) {
        N = graph.size();
        vector<vector<int> > result;
        vector<int> path(1, 0);
        dfs(0, path, result, graph);
        return result;
    }
};