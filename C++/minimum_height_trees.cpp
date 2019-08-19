/*
310. Minimum Height Trees
For a undirected graph with tree characteristics,
we can choose any node as the root.
The result graph is then a rooted tree.
Among all possible rooted trees,
those with minimum height are called minimum height trees (MHTs).
Given such a graph, write a function to find all the MHTs and return a list of their root labels.

Format
The graph contains n nodes which are labeled from 0 to n - 1.
You will be given the number n and a list of undirected edges (each edge is a pair of labels).

You can assume that no duplicate edges will appear in edges.
Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

Example 1 :

Input: n = 4, edges = [[1, 0], [1, 2], [1, 3]]

  0
  |
  1
 /  \
2   3

Output: [1]
Example 2 :

Input: n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]
  0  1  2
  \ | /
    3
    |
    4
    |
    5

Output: [3, 4]

Note:
According to the definition of tree on Wikipedia:
“a tree is an undirected graph in which any two vertices are connected by exactly one path.
In other words, any connected graph without simple cycles is a tree.”
The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.
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
/*
Longest Path

It is easy to see that the root of an MHT has to be the middle point (or two middle points) of the longest path of the tree.
Though multiple longest paths can appear in an unrooted tree, they must share the same middle point(s).

Computing the longest path of a unrooted tree can be done, in O(n) time, by tree dp, or simply 2 tree traversals (dfs or bfs).
The following is some thought of the latter.

Randomly select a node x as the root, do a dfs/bfs to find the node y that has the longest distance from x.
Then y must be one of the endpoints on some longest path.
Let y the new root, and do another dfs/bfs. Find the node z that has the longest distance from y.

Now, the path from y to z is the longest one, and thus its middle point(s) is the answer.
https://github.com/lydxlx1/LeetCode/blob/master/src/_310.java
*/

// delete the nodes layer by layer from all the leaf nodes
// until there are only 2 or less nodes left
class Solution { // 76.63%
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) {
            return {0};
        }

        vector<vector<int>> graph(n);
        vector<int> degree(n, 0);
        for (vector<int> edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
            degree[edge[0]] += 1;
            degree[edge[1]] += 1;
        }

        queue<int> leaves;
        for (int i = 0; i < n; ++i) {
            if (degree[i] == 1) {
                leaves.push(i);
            }
        }

        while (n > 2) {
            int curSize = leaves.size();
            n -= curSize;
            for (int i = 0; i < curSize; ++i) {
                int cur = leaves.front();
                leaves.pop();
                for (int node : graph[cur]) {
                    if (degree[node] == 0) {
                        continue;
                    }
                    if (degree[node] == 2) {
                        leaves.push(node);
                    }
                    degree[node] -= 1;
                }
            }
        }

        vector<int> result;
        while (!leaves.empty()) {
            result.push_back(leaves.front());
            leaves.pop();
        }
        return result;
    }
};

class Solution1 { // 5.06%
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) {
            return {0};
        }

        vector<unordered_set<int>> graph(n);
        for (vector<int> edge : edges) {
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
        }

        queue<int> leaves;
        for (int i = 0; i < n; ++i) {
            if (graph[i].size() == 1) {
                leaves.push(i);
            }
        }
        while (n > 2) {
            int curSize = leaves.size();
            n -= curSize;
            for (int i = 0; i < curSize; ++i) {
                int cur = leaves.front();
                leaves.pop();
                for (int parent : graph[cur]) {
                    graph[parent].erase(cur);
                    if (graph[parent].size() == 1) {
                        leaves.push(parent);
                    }
                }
            }
        }

        vector<int> result;
        while (!leaves.empty()) {
            result.push_back(leaves.front());
            leaves.pop();
        }
        return result;
    }
};

class Solution1 { // time limit exceeded
private:
    void dfs(unordered_map<int, vector<int>>& graph, vector<bool>& visited, vector<int>& path,
             unordered_set<int>& result, int& maxLength) {
        int cur = path.back();
        if (visited[cur]) {
            return;
        }

        if (graph[cur].size() == 1) {
            if (path.size() >= maxLength) {
                if (path.size() > maxLength) {
                    result.clear();
                }
                maxLength = path.size();
                result.insert(path[maxLength / 2]);
                if (maxLength % 2 == 0) {
                    result.insert(path[maxLength / 2 - 1]);
                }
            }
            return;
        }

        for (int next : graph[cur]) {
            if (path.size() <= 1 || next != path[path.size() - 2]) {
                path.push_back(next);
                dfs(graph, visited, path, result, maxLength);
                path.pop_back();
            }
        }
    }
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) {
            return {0};
        }
        unordered_map<int, vector<int>> graph;
        for (vector<int> edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        vector<bool> visited(n, false);
        vector<int> path;
        int maxLength = 0;
        unordered_set<int> result;
        for (int i = 0; i < n; i++) {
            if (graph[i].size() == 1) {
                path.push_back(i);
                path.push_back(graph[i].front());
                dfs(graph, visited, path, result, maxLength);
                visited[i] = true;
            }
            path.clear();
        }
        return vector<int>(result.begin(), result.end());
    }
};
