/*
1443. Minimum Time to Collect All Apples in a Tree
https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/

Given an undirected tree consisting of n vertices numbered from 0 to n-1,
which has some apples in their vertices.
You spend 1 second to walk over one edge of the tree.
Return the minimum time in seconds you have to spend
in order to collect all apples in the tree starting at vertex 0 and coming back to this vertex.

The edges of the undirected tree are given in the array edges,
where edges[i] = [fromi, toi] means that exists an edge connecting the vertices fromi and toi.
Additionally, there is a boolean array hasApple,
where hasApple[i] = true means that vertex i has an apple,
otherwise, it does not have any apple.

Example 1:
Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,true,false,true,true,false]
Output: 8
Explanation: The figure above represents the given tree where red vertices have an apple. One optimal path to collect
all apples is shown by the green arrows.

Example 2:
Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,true,false,false,true,false]
Output: 6
Explanation: The figure above represents the given tree where red vertices have an apple. One optimal path to collect
all apples is shown by the green arrows.

Example 3:
Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,false,false,false,false,false]
Output: 0

Constraints:
1 <= n <= 10^5
edges.length == n-1
edges[i].length == 2
0 <= fromi, toi <= n-1
fromi < toi
hasApple.length == n
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
#include <climits>
#include <map>
#include <set>
#include <numeric>
using namespace std;

class Solution {
private:
    vector<vector<int>> adjList;
    int dfs(vector<bool>& hasApple, int root, int prev) {
        int result = 0;
        for (int child : adjList[root]) {
            if (child != prev) {
                int temp = dfs(hasApple, child, root);
                if (temp != 0 or hasApple[child]) {
                    result += temp + 2;
                }
            }
        }
        return (result != 0 or hasApple[root]) ? result : 0;
    }

public:
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        adjList.resize(n);
        for (vector<int>& e : edges) {
            adjList[e[0]].push_back(e[1]);
            adjList[e[1]].push_back(e[0]);
        }
        return dfs(hasApple, 0, -1);
    }
};
