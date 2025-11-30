/*
1203. Sort Items by Groups Respecting Dependencies
https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/

There are n items each belonging to zero or one of m groups
where group[i] is the group that the i-th item belongs to
and it's equal to -1 if the i-th item belongs to no group.
The items and the groups are zero indexed.
A group can have no item belonging to it.

Return a sorted list of the items such that:
The items that belong to the same group are next to each other in the sorted list.
There are some relations between these items
where beforeItems[i] is a list containing all the items that should come before the i-th item in the sorted array
(to the left of the i-th item).
Return any solution if there is more than one solution and return an empty list if there is no solution.

Example 1:
Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]]
Output: [6,3,4,1,5,2,0,7]

Example 2:
Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3],[],[4],[]]
Output: []
Explanation: This is the same as example 1 except that 4 needs to be before 6 in the sorted list.

Constraints:
1 <= m <= n <= 3*10^4
group.length == beforeItems.length == n
-1 <= group[i] <= m-1
0 <= beforeItems[i].length <= n-1
0 <= beforeItems[i][j] <= n-1
i != beforeItems[i][j]
beforeItems[i] does not contain duplicates elements.
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
#include <numeric>
using namespace std;
/*
We do a two-level topological sort according to beforeItems.

Group level. Decide which group should go first.
Inner-group level. Decide which item should go first.
Isolated items (-1) can be put into separate groups to make the solution simpler.
*/
class Graph {
    unordered_map<int, vector<int>> adj;
    unordered_map<int, int> indegree;

public:
    Graph() {
    }

    Graph(int n) {
        for (int i = 0; i < n; ++i) {
            indegree[i] = 0;
        }
    }

    Graph(vector<int>& vec) {
        for (const int& i : vec) {
            indegree[i] = 0;
        }
    }

    void addEdge(int from, int to) {
        adj[from].push_back(to);
        indegree[to] += 1;
    }

    vector<int> sort() {
        queue<int> q;
        for (const auto& p : indegree)
            if (p.second == 0) {
                q.push(p.first);
            }

        vector<int> result;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            result.push_back(cur);
            for (const auto& next : adj[cur]) {
                indegree[next] -= 1;
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        return result;
    }
};

class Solution {
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        vector<vector<int>> groupItems(m + 1);
        for (int i = 0; i < n; ++i) {
            if (group[i] >= 0) {
                groupItems[group[i]].push_back(i);
            } else {  // Isolated items are put into separate groups.
                group[i] = m;
                groupItems[m].push_back(i);
            }
        }

        vector<Graph> groupItemGraphs(groupItems.size());
        for (int i = 0; i < groupItems.size(); ++i) {
            groupItemGraphs[i] = Graph(groupItems[i]);
        }

        Graph groupGraph = Graph(groupItems.size());
        for (int i = 0; i < n; ++i) {
            int curGroup = group[i];
            for (const int& item : beforeItems[i]) {
                int beforeGroup = group[item];
                if (curGroup == beforeGroup) {  // BeforeItem is in the same group, add edge in the graph of that group.
                    groupItemGraphs[curGroup].addEdge(item, i);
                } else {  // BeforeItem is in a different group, add edge in the graph of groups.
                    groupGraph.addEdge(beforeGroup, curGroup);
                }
            }
        }

        vector<int> groupOrder = groupGraph.sort();
        if (groupOrder.size() < groupItems.size()) {
            return {};
        }

        vector<int> result;
        for (const int& i : groupOrder) {
            vector<int> order = groupItemGraphs[i].sort();
            if (order.size() < groupItems[i].size()) {
                return {};
            }

            for (const int& j : order) {
                result.push_back(j);
            }
        }
        return result;
    }
};
