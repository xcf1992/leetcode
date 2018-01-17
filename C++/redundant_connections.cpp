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
    int find(vector<int>& parent, int node) {
        return parent[node] == 0 ? node : find(parent, parent[node]);
    }
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<int> parent(n, 0);
        for (auto edge : edges) {
            int start = edge[0];
            int end = edge[1];
            
            int parentX = find(parent, start);
            int parentY = find(parent, end);
            if (parentX == parentY) {
                return edge;
            }
            
            parent[parentX] = parentY;
        }
    }
};
