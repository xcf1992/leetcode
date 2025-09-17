/*
1514. Path with Maximum Probability
https://leetcode.com/problems/path-with-maximum-probability/

You are given an undirected weighted graph of n nodes (0-indexed),
represented by an edge list where edges[i] = [a, b] is an undirected edge connecting the nodes a and b
with a probability of success of traversing that edge succProb[i].

Given two nodes start and end,
find the path with the maximum probability of success to go from start to end and return its success probability.

If there is no path from start to end, return 0.
Your answer will be accepted if it differs from the correct answer by at most 1e-5.

Example 1:
Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
Output: 0.25000
Explanation: There are two paths from start to end, one having a probability of success = 0.2 and the other has 0.5 * 0.5 = 0.25.

Example 2:
Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0, end = 2
Output: 0.30000

Example 3:
Input: n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
Output: 0.00000
Explanation: There is no path between 0 and 2.

Constraints:
2 <= n <= 10^4
0 <= start, end < n
start != end
0 <= a, b < n
a != b
0 <= succProb.length == edges.length <= 2*10^4
0 <= succProb[i] <= 1
There is at most one edge between every two nodes.
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
#include <stdio.h>
#include <set>
using namespace std;

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        unordered_map<int, vector<pair<int, double>>> next;
        for (int i = 0; i < edges.size(); ++i) {
            int from = edges[i][0];
            int to = edges[i][1];
            double prob = succProb[i];

            next[from].push_back({to, prob});
            next[to].push_back({from, prob});
        }

        vector<double> reachProb(n, 0.0);
        reachProb[start] = 1.0;
        queue<pair<int, double>> bfs;
        bfs.push({start, 1.0});
        while (!bfs.empty()) {
            int curPos = bfs.front().first;
            double curProb = bfs.front().second;
            bfs.pop();

            for (pair<int, double>& nxt: next[curPos]) {
                int to = nxt.first;
                double prob = nxt.second;
                double newProb = prob * curProb;
                if (newProb > reachProb[to]) {
                    reachProb[to] = newProb;
                    bfs.push({to, newProb});
                }
            }
        }
        return reachProb[end];
    }
};
