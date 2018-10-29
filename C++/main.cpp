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
    int minMalwareSpread(vector<vector<int>> graph, vector<int> initial) {
        int nodes = graph.size();
        unordered_set<int> initialInfections(initial.begin(), initial.end());
        unordered_map<int, unordered_set<int>> infectedBy;
        queue<pair<int, int>> bfs;
        for (int i : initial) {
            infectedBy[i].insert(i);
            bfs.push({i, i});
        }
        
        while (!bfs.empty()) {
            int curNode = bfs.front().first;
            int source = bfs.front().second;
            bfs.pop();
            
            for (int nextNode = 0; nextNode < graph[curNode].size(); nextNode++) {
                if (nextNode != curNode && graph[curNode][nextNode] == 1 && infectedBy[nextNode].find(source) == infectedBy[nextNode].end() && initialInfections.find(nextNode) == initialInfections.end()) {
                    infectedBy[nextNode].insert(source);
                    bfs.push({nextNode, source});
                }
            }
        }
        
        unordered_map<int, int> onlySource;
        for (auto& infection : infectedBy) {
            int node = infection.first;
            unordered_set<int> sources = infection.second;
            if (sources.size() == 1) {
                for (int source : sources) {
                    onlySource[source] += 1;
                }
            }
        }
        
        int count = INT_MIN;
        int result = -1;
        for (auto& os : onlySource) {
            if (count < os.second) {
                count = os.second;
                result = os.first;
            }
            else if (count == os.second) {
                result = min(result, os.first);
            }
        }
        return result;
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
    
    s.minMalwareSpread({{1,1,0}, {1,1,1}, {0,1,1}}, {0,1});
    return 0;
}
