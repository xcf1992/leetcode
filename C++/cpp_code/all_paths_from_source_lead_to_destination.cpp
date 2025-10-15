/*
1059. All Paths from Source Lead to Destination
Given the edges of a directed graph,
and two nodes source and destination of this graph,
determine whether or not all paths starting from source eventually end at destination,

that is:
At least one path exists from the source node to the destination node
If a path exists from the source node to a node with no outgoing edges, then that node is equal to destination.
The number of possible paths from source to destination is a finite number.
Return true if and only if all roads from source lead to destination.

Example 1:
            0 (source)
        /       \
       1         2 (destination)
Input: n = 3, edges = [[0,1],[0,2]], source = 0, destination = 2
Output: false
Explanation: It is possible to reach and get stuck on both node 1 and node 2.

Example 2:



Input: n = 4, edges = [[0,1],[0,3],[1,2],[2,1]], source = 0, destination = 3
Output: false
Explanation: We have two possibilities: to end at node 3, or to loop over node 1 and node 2 indefinitely.
Example 3:



Input: n = 4, edges = [[0,1],[0,2],[1,3],[2,3]], source = 0, destination = 3
Output: true
Example 4:



Input: n = 3, edges = [[0,1],[1,1],[1,2]], source = 0, destination = 2
Output: false
Explanation: All paths from the source node end at the destination node, but there are an infinite number of paths,
such as 0-1-2, 0-1-1-2, 0-1-1-1-2, 0-1-1-1-1-2, and so on.
Example 5:



Input: n = 2, edges = [[0,1],[1,1]], source = 0, destination = 1
Output: false
Explanation: There is infinite self-loop at destination node.


Note:

The given graph may have self loops and parallel edges.
The number of nodes n in the graph is between 1 and 10000
The number of edges in the graph is between 0 and 10000
0 <= edges.length <= 10000
edges[i].length == 2
0 <= source <= n - 1
0 <= destination <= n - 1
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
    bool dfs(vector<vector<int>>& connect, int from, int to, vector<int>& visited) {
        if (connect[from].empty()) {
            return from == to;
        }

        if (visited[from] == -1) { // if from is visited, it must be a true case
            return true;
        }

        if (visited[from] == 1) { // if from is visiting, it comes again, it means a loop
            return false;
        }

        visited[from] = 1; //set to visiting
        for (int next : connect[from]) {
            if (!dfs(connect, next, to, visited)) {
                return false;
            }
        }
        visited[from] = -1; //set to visited
        return true;
    }
public:
    bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
        vector<vector<int>> connect(n);
        for (vector<int>& edge : edges) {
            connect[edge[0]].push_back(edge[1]);
        }
        vector<int> visited(n, 0);
        return dfs(connect, source, destination, visited);
    }
};
