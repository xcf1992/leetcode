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
    bool canFlow(vector<vector<int>>& matrix, vector<vector<int>>& flowTo, int i, int j, int x, int y) {
        int m = matrix.size();
        int n = matrix[0].size();
        if (x >= m || y >= n || x < 0 || y < 0) {
            return false;
        }
        
        if (matrix[x][y] > matrix[i][j]) {
            return false;
        }
        
        if (flowTo[x][y] == 1) {
            return true;
        }
        
        if (flowTo[x][y] == 0) {
            return false;
        }
        
        if (canFlow(matrix, flowTo, x, y, x - 1, y) ||
            canFlow(matrix, flowTo, x, y, x + 1, y) ||
            canFlow(matrix, flowTo, x, y, x, y - 1) ||
            canFlow(matrix, flowTo, x, y, x, y + 1)) {
            flowTo[x][y] = 1;
            return true;
        }
        flowTo[x][y] = 0;
        return false;
    }
public:
    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) {
            return {};
        }
        int n = matrix[0].size();
        
        vector<vector<int>> flow2P(m, vector<int>(n, -1));
        vector<vector<int>> flow2A(m, vector<int>(n, -1));
        for (int i = 0; i < m; i++) {
            flow2P[i][0] = 1;
            flow2A[i][n - 1] = 1;
        }
        for (int j = 0; j < n; j++) {
            flow2P[0][j] = 1;
            flow2A[m - 1][j] = 1;
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (flow2P[i][j] == -1) {
                    if (canFlow(matrix, flow2P, i, j, i - 1, j) ||
                        canFlow(matrix, flow2P, i, j, i + 1, j) ||
                        canFlow(matrix, flow2P, i, j, i, j - 1) ||
                        canFlow(matrix, flow2P, i, j, i, j + 1)) {
                        flow2P[i][j] = 1;
                    }
                    else {
                        flow2P[i][j] = 0;
                    }
                }
                
                if (flow2A[i][j] == -1) {
                    if (canFlow(matrix, flow2A, i, j, i - 1, j) ||
                        canFlow(matrix, flow2A, i, j, i + 1, j) ||
                        canFlow(matrix, flow2A, i, j, i, j - 1) ||
                        canFlow(matrix, flow2A, i, j, i, j + 1)) {
                        flow2A[i][j] = 1;
                    }
                    else {
                        flow2A[i][j] = 0;
                    }
                }
            }
        }
        
        vector<pair<int, int>> result;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (flow2P[i][j] == 1 && flow2A[i][j] == 1) {
                    result.push_back(make_pair(i, j));
                }
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> v1({1,0,0,0,0,1});
    vector<int> v2({0,4});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{1,2,2,3,5}, {3,2,3,4,4}, {2,4,5,3,1}, {6,7,1,4,5}, {5,1,1,2,4}});
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(4,3));
    fuxk.push_back(make_pair(2,3));
    fuxk.push_back(make_pair(2,1));
    fuxk.push_back(make_pair(5,0));
    
    s.pacificAtlantic(matrix);
}
