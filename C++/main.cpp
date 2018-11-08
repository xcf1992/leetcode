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
public:
    int reachableNodes(vector<vector<int>> edges, int M, int N) {
        unordered_map<int, vector<int>> next;
        unordered_map<int, unordered_map<int, int>> distance;
        unordered_map<int, unordered_map<int, int>> used;
        for (vector<int>& edge : edges) {
            int start = edge[0];
            int end = edge[1];
            next[start].push_back(end);
            next[end].push_back(start);
            distance[start][end] = edge[2];
            distance[end][start] = edge[2];
            used[start][end] = 0;
            used[end][start] = 0;
        }
        
        unordered_map<int, int> visited;
        queue<pair<int, int>> bfs;
        bfs.push({0, M});
        visited[0] = M;
        while (!bfs.empty()) {
            int cur = bfs.front().first;
            int leftMove = bfs.front().second;
            bfs.pop();
            
            for (int node : next[cur]) {
                if (leftMove >= distance[cur][node] + 1) {
                    used[cur][node] = distance[cur][node];
                    if (leftMove - distance[cur][node] - 1 > visited[node]) {
                        bfs.push({node, leftMove - distance[cur][node] - 1});
                        visited[node] = leftMove - distance[cur][node] - 1;
                    }
                }
                else {
                    if (leftMove > used[cur][node]) {
                        used[cur][node] = leftMove;
                    }
                }
            }
        }
        
        int usedNodes = 0;
        for (auto it = used.begin(); it != used.end(); it++) {
            int start = it -> first;
            unordered_map<int, int> usage = it -> second;
            for (auto it2 = usage.begin(); it2 != usage.end(); it2++) {
                int end = it2 -> first;
                usedNodes += min(distance[start][end], it2 -> second + used[end][start]);
                used[start][end] = 0;
                used[end][start] = 0;
            }
        }
        return usedNodes + visited.size();
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
    vector<vector<int>> vb({{3,0}});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({
        {1,1,1,0,1,1,1,1},
        {1,0,0,0,0,1,1,1},
        {1,1,1,0,0,0,1,1},
        {1,1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0}
    });
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    vector<vector<int>> matrix3({
        {1,0},
        {0,1}
    });
    
    int x = s.reachableNodes({{3,4,8},{0,1,3},{1,4,0},{1,2,3},{0,3,2},{0,4,10},{1,3,3},{2,4,3},{2,3,3},{0,2,10}}, 7, 5);
    return 0;
}
