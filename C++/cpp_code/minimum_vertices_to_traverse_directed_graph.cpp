/*
https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=273389
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
    void dfs(unordered_set<int>& result, vector<unordered_set<int>>& graph, unordered_set<int>& visited,
             unordered_set<int>& curPath, int cur, int start) {
        curPath.insert(cur);
        visited.insert(cur);
        for (int nxt : graph[cur]) {
            if (result.find(nxt) != result.end() and nxt != start) {
                result.erase(cur);
            }
            if (curPath.find(nxt) == curPath.end()) {
                dfs(result, graph, visited, curPath, nxt, start);
            }
        }
    }

public:
    vector<int> getMinimumVetricesCount(vector<vector<int>>& edges, int n) {
        vector<unordered_set<int>> graph(n);
        for (vector<int>& edge : edges) {
            graph[edge[0]].insert(edge[1]);
        }

        unordered_set<int> result;
        unordered_set<int> visited;
        for (int i = 0; i < n; ++i) {
            if (visited.find(i) == visited.end()) {
                result.insert(i);
                visited.insert(i);
                unordered_set<int> curPath;
                dfs(result, graph, visited, curPath, i, i);
            }
        }
        return vector<int>(result.begin(), result.end());
    }
};
