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
    void bfs(int n, int start, vector<int>& furthest, vector<vector<int>>& connect) {
        vector<bool> visited(n, false);
        visited[start] = true;

        queue<int> bfs;
        bfs.push(start);

        while (!bfs.empty()) {
            int cur_size = bfs.size();
            furthest.clear();
            for (int i = 0; i < cur_size; i++) {
                int cur = bfs.front();
                bfs.pop();

                furthest.push_back(cur);
                for (int next : connect[cur]) {
                    if (visited[next]) {
                        continue;
                    }

                    visited[next] = true;
                    bfs.push(next);
                }
            }
        }
    }
public:
    string findSpecialNodes(int n, vector<vector<int>>& edges) {
        vector<vector<int>> connect(n, vector<int>());
        for (vector<int>& e : edges) {
            connect[e[0]].push_back(e[1]);
            connect[e[1]].push_back(e[0]);
        }

        vector<int> furthest;
        bfs(n, 0, furthest, connect);

        vector<int> endpoints;
        bfs(n, furthest[0], endpoints, connect);
        endpoints.push_back(furthest[0]);

        string rst(n, '0');
        for (int idx : endpoints) {
            rst[idx] = '1';
        }
        return rst;
    }
};

int main() {
    vector<vector<int>> edges({{0,1}, {1,2}, {2,3}, {3,4}, {3,5}, {1,6}});

    Solution s;
    s.findSpecialNodes(7, edges);
    return 0;
}
