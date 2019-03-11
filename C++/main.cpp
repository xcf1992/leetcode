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

class Solution {
private:
    int find(vector<int>& parent, int node) {
        return parent[node] == 0 ? node : find(parent, parent[node]);
    }
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>> edges) {
        int n = edges.size();
        vector<int> parent(n + 1, 0);
        vector<vector<int>> result;
        for (vector<int>& edge : edges) {
            if (parent[edge[1]] == 0) {
                parent[edge[1]] = parent[edge[0]];
            }
            else {
                result.push_back({parent[edge[1]], edge[1]});
                result.push_back(edge);
                edge[1] = 0;
            }
        }
        
        for (int i = 0; i <= n; i++) {
            parent[i] = 0;
        }
        for (vector<int>& edge : edges) {
            if (edge[1] == 0) {
                continue;
            }
            
            int p = edge[0];
            int c = edge[1];
            int cur = find(parent, p);
            if (cur == c) {
                if (result.empty()) {
                    return edge;
                }
                // cause currently we have removed result[1] already but still has circle
                return result[0];
            }
            parent[c] = cur;
        }
        return result[1];
    }
};

int main() {
    Solution s;
    s.findRedundantDirectedConnection({{3,1},{2,1},{4,2},{1,4}});
    return 0;
}
