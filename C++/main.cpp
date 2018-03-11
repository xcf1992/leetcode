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
private:
    int N;
    void dfs(int cur, vector<int> path, vector<vector<int>>& result, vector<vector<int>>& graph) {
        if (cur == N - 1) {
            result.push_back(path);
            return;
        }
        
        for (int next : graph[cur]) {
            path.push_back(next);
            dfs(next, path, result, graph);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        N = graph.size() ;
        vector<vector<int>> result;
        vector<int> path(1, 0);
        dfs(0, path, result, graph);
        return result;
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v2({-4,-2,2,4});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{1,2},{3},{3},{}});
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(0, 1));
    fuxk.push_back(make_pair(1, 2));
    fuxk.push_back(make_pair(3, 4));
    
    s.allPathsSourceTarget(matrix);
}
