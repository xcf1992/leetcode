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
    int X;
    int Y;
    int Z;
    bool find;
    
    void dfs(int curX, int curY, vector<vector<bool>>& visited) {
        if (visited[curX][curY] || find) {
            return;
        }
        if (curX == Z || curY == Z) {
            find = true;
            return;
        }
        visited[curX][curY] = true;
        if (curX != 0) {
            dfs(0, curY, visited);
            if (find) {
                return;
            }
        }
        if (curY != 0) {
            dfs(curX, 0, visited);
            if (find) {
                return;
            }
        }
        if (curX != X) {
            dfs(X, curY, visited);
            if (find) {
                return;
            }
        }
        if (curY != Y) {
            dfs(curX, Y, visited);
            if (find) {
                return;
            }
        }
        if (curX != X) {
            int gap = X - curX;
            if (gap > curY) {
                dfs(curX + curY, 0, visited);
                if (find) {
                    return;
                }
            }
            else {
                dfs(X, curY - gap, visited);
                if (find) {
                    return;
                }
            }
        }
        if (curY != Y) {
            int gap = Y - curY;
            if (gap > curX) {
                dfs(0, curX + curY, visited);
                if (find) {
                    return;
                }
            }
            else {
                dfs(curX - gap, Y, visited);
                if (find) {
                    return;
                }
            }
        }
    }
public:
    bool canMeasureWater(int x, int y, int z) {
        if (z < 0 || z > x + y) {
            return false;
        }
        X = x;
        Y = y;
        Z = z;
        find = false;
        vector<vector<bool>> visited(x + 1, vector<bool>(y + 1, false));
        dfs(0, 0, visited);
        return find;
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v2({4,2});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{4,3}, {2,3}, {2,1}, {5,0}, {0,1}});
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(4,3));
    fuxk.push_back(make_pair(2,3));
    fuxk.push_back(make_pair(2,1));
    fuxk.push_back(make_pair(5,0));
    
    s.canMeasureWater(22003, 31237, 1);
}
