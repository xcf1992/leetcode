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
    void update(int house, int distance, int posI, int posJ, vector<vector<int>>& shortest, unordered_map<int, unordered_set<int>>& visited, queue<vector<int>>& bfs, vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        if (posI < 0 || posJ < 0 || posI >= m || posJ >= n || grid[posI][posJ] != 0) {
            return;
        }
        
        int newPos = posI * n + posJ;
        if (visited[newPos].find(house) != visited[newPos].end()) {
            return;
        }
        
        shortest[posI][posJ] += distance;
        visited[newPos].insert(house);
        bfs.push({house, distance, newPos});
    }
public:
    int shortestDistance(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        unordered_map<int, unordered_set<int>> visited; // pos hae been visited by house x
        queue<vector<int>> bfs; // insert pair <house, distance, pos> the distance house x reach pos
        int house = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    bfs.push({house, 0, i * n + j});
                    visited[i * m + j].insert(house);
                    house += 1;
                }
            }
        }
        
        vector<vector<int>> shortest(m, vector<int>(n, 0));
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; i++) {
                int curHouse = bfs.front()[0];
                int curDistance = bfs.front()[1];
                int posI = bfs.front()[2] / n;
                int posJ = bfs.front()[2] % n;
                bfs.pop();
                
                update(curHouse, curDistance + 1, posI - 1, posJ, shortest, visited, bfs, grid);
                update(curHouse, curDistance + 1, posI + 1, posJ, shortest, visited, bfs, grid);
                update(curHouse, curDistance + 1, posI, posJ - 1, shortest, visited, bfs, grid);
                update(curHouse, curDistance + 1, posI, posJ + 1, shortest, visited, bfs, grid);
            }
        }
        
        int result = INT_MAX;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0 && visited[i * n + j].size() == house) {
                    result = min(result, shortest[i][j]);
                }
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
    vector<int> vb({3,2});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({{1,0,2,0,1}, {0,0,0,0,0}, {0,0,1,0,0}});
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    
    s.shortestDistance(matrix1);
    return 0;
}
