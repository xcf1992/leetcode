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
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        unordered_map<int, vector<int>> adj;
        for (auto edge : edges) {
            adj[edge.first].push_back(edge.second);
            adj[edge.second].push_back(edge.first);
        }
        
        vector<bool> visited(n, false);
        int result = 0;
        for (int i = 0; i < n && !visited[i]; i++) {
            visited[i] = true;
            result += 1;
            queue<int> connected;
            connected.push(i);
            while (!connected.empty()) {
                int cur = connected.front();
                connected.pop();
                
                for (int node : adj[cur]) {
                    if (!visited[node]) {
                        visited[node] = true;
                        connected.push(node);
                    }
                }
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v2({2,2,2,2,2});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{0,1},{1,2},{3,4}});
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(0, 1));
    fuxk.push_back(make_pair(1, 2));
    fuxk.push_back(make_pair(3, 4));
    s.countComponents(5, fuxk);
}
