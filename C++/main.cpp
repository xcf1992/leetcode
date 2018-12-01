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
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>> edges) {
        unordered_map<int, vector<int>> connected;
        for (vector<int>& edge : edges) {
            connected[edge[0]].push_back(edge[1]);
            connected[edge[1]].push_back(edge[0]);
        }
        
        vector<int> result(N, 0);
        vector<vector<bool>> visited(N, vector<bool>(N, false));
        queue<vector<int>> bfs;
        for (int i = 0; i < N; i++) {
            bfs.push({i, i}); // {from, cur}
            visited[i][i] = true;
        }
        
        int distance = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; i++) {
                int source = bfs.front()[0];
                int cur = bfs.front()[1];
                bfs.pop();
                result[source] += 1;
                for (int next : connected[cur]) {
                    if (!visited[source][next]) {
                        visited[source][next] = true;
                        bfs.push({source, next});
                    }
                }
            }
            distance += 1;
        }
        return result;
    }
};

int main() {
    vector<bool> visited(10, false);
    visited[2] = true;
    visited[7] = true;
    visited[4] = true;
    visited.resize(10, false);
    visited.clear();
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
    s.sumOfDistancesInTree(6,{{0,1},{0,2},{2,3},{2,4},{2,5}});
    return 0;
}
