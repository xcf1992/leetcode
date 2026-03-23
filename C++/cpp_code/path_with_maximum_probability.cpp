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
Explanation: There are two paths from start to end, one having a probability of success = 0.2 and the other has 0.5 *
0.5 = 0.25.

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
#include <climits>
#include <set>
using namespace std;

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        unordered_map<int, vector<pair<int, double>>> adj;
        for (int i = 0; i < edges.size(); ++i) {
            int from = edges[i][0];
            int to = edges[i][1];
            double prob = succProb[i];

            adj[from].push_back({to, prob});
            adj[to].push_back({from, prob});
        }

        vector<double> reach_prob(n, 0.0);
        reach_prob[start] = 1.0;

        queue<pair<int, double>> bfs;
        bfs.push({start, 1.0});
        while (!bfs.empty()) {
            int cur_pos = bfs.front().first;
            double cur_prob = bfs.front().second;
            bfs.pop();

            for (pair<int, double>& nxt : adj[cur_pos]) {
                int to = nxt.first;
                double prob = nxt.second;
                double new_prob = prob * cur_prob;
                if (new_prob > reach_prob[to]) {
                    reach_prob[to] = new_prob;
                    bfs.push({to, new_prob});
                }
            }
        }
        return reach_prob[end];
    }
};

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        unordered_map<int, vector<pair<double, int>>> graph;
        for (int i = 0; i < edges.size(); ++i) {
            int from = edges[i][0];
            int to = edges[i][1];
            double prob = succProb[i];
            graph[from].push_back({prob, to});
            graph[to].push_back({prob, from});
        }

        vector<double> max_prob(n, 0.0);
        max_prob[start] = 1.0;

        // please note that the priority queue in c++ is a max heap by default
        // and the sorting is decided by the first element of the pair.
        priority_queue<pair<double, int>> pq;
        pq.push({1.0, start});
        while (!pq.empty()) {
            double cur_prob = pq.top().first;
            int cur_node = pq.top().second;
            pq.pop();

            if (cur_prob < max_prob[cur_node]) {
                continue;
            }

            if (cur_node == end) {
                return cur_prob;
            }

            if (!graph[cur_node].empty()) {  // Check if the node has been processed
                for (auto& nxt : graph[cur_node]) {
                    int next_node = nxt.second;
                    double new_prob = nxt.first;
                    if (cur_prob * new_prob > max_prob[next_node]) {
                        max_prob[next_node] = cur_prob * new_prob;
                        pq.push({max_prob[next_node], next_node});
                    }
                }
                graph[cur_node].clear();  // Clear the adjacency list by removing the entry
            }
        }

        return 0.0;
    }
};
