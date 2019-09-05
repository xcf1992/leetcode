/*
802. Find Eventual Safe States
 In a directed graph, we start at some node and every turn, walk along a directed edge of the graph.  If we reach a node that is terminal (that is, it has no outgoing directed edges), we stop.

 Now, say our starting node is eventually safe if and only if we must eventually walk to a terminal node.  More specifically, there exists a natural number K so that for any choice of where to walk, we must have stopped at a terminal node in less than K steps.

 Which nodes are eventually safe?  Return them as an array in sorted order.

 The directed graph has N nodes with labels 0, 1, ..., N-1, where N is the length of graph.  The graph is given in the following form: graph[i] is a list of labels j such that (i, j) is a directed edge of the graph.

 Example:
 Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
 Output: [2,4,5,6]
 Here is a diagram of the above graph.

 Illustration of graph

 Note:

 graph will have length at most 10000.
 The number of edges in the graph will not exceed 32000.
 Each graph[i] will be a sorted list of different integers, chosen within the range [0, graph.length - 1].
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
private:
    bool eventualSafe(vector<vector<int>>& graph, int node, vector<int>& visited) {
        if (visited[node] != 0) {
            return visited[node] == 1;
        }

        visited[node] = -1;
        for (int next : graph[node]) {
            if (!eventualSafe(graph, next, visited)) {
                return false;
            }
        }
        visited[node] = 1;
        return true;
    }
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int nodes = graph.size();
        vector<int> result;
        vector<int> visited(nodes, 0);
        for (int i = 0; i < nodes; i++) {
            if (eventualSafe(graph, i, visited)) {
                result.push_back(i);
            }
        }
        return result;
    }
};
