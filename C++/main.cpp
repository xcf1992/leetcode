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
#include <set>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    void dfs(int x, int y, string& island, vector<vector<int>>& grid, vector<vector<bool>>& visited) {
        int m = grid.size();
        int n = grid[0].size();
        
        if (x + 1 < m && !visited[x + 1][y] && grid[x + 1][y] == 1) {
            island.push_back('d');
            visited[x + 1][y] = true;
            dfs(x + 1, y, island, grid, visited);
        }
        if (x - 1 >= 0 && !visited[x - 1][y] && grid[x - 1][y] == 1) {
            island.push_back('u');
            visited[x - 1][y] = true;
            dfs(x - 1, y, island, grid, visited);
        }
        if (y + 1 < n && !visited[x][y + 1] && grid[x][y + 1] == 1) {
            island.push_back('r');
            visited[x][y + 1] = true;
            dfs(x, y + 1, island, grid, visited);
        }
        if (y - 1 >= 0 && !visited[x][y - 1] && grid[x][y - 1] == 1) {
            island.push_back('l');
            visited[x][y - 1] = true;
            dfs(x, y - 1, island, grid, visited);
        }
    }
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        int m = grid.size();
        if (m == 0) {
            return 0;
        }
        int n = grid[0].size();
        unordered_set<string> shape;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    string island = "";
                    visited[i][j] = true;
                    dfs(i, j, island, grid, visited);
                    if (shape.find(island) == shape.end()) {
                        shape.insert(island);
                    }
                }
            }
        }
        return shape.size();
    }
};
int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v2({4,2});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{1,1,0}, {0,1,1}, {0,0,0}, {1,1,1}, {0,1,0}});
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(0, 1));
    fuxk.push_back(make_pair(1, 2));
    fuxk.push_back(make_pair(3, 4));
    
    s.numDistinctIslands(matrix);
}
