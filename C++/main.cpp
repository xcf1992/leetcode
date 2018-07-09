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
    int mod = 1e9 + 7;
public:
    int findPaths(int m, int n, int N, int i, int j) {
        if (N == 0) {
            return 0;
        }
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(m, vector<int>(n, 0)));
        for (int y = 0; y < n; y++) {
            dp[0][0][y] += 1;
            dp[0][m - 1][y] += 1;
        }
        for (int x = 0; x < m; x++) {
            dp[0][x][0] += 1;
            dp[0][x][n - 1] += 1;
        }
        for (int k = 1; k < N; k++) {
            for (int x = 0; x < m; x++) {
                for (int y = 0; y < n; y++) {
                    dp[k][x][y] = dp[k - 1][x][y];
                    if (i - 1 >= 0) {
                        dp[k][x][y] += dp[k - 1][x - 1][y];
                        dp[k][x][y] %= mod;
                    }
                    if (i + 1 < m) {
                        dp[k][x][y] += dp[k - 1][x + 1][y];
                        dp[k][x][y] %= mod;
                    }
                    if (j - 1 >= 0) {
                        dp[k][x][y] += dp[k - 1][x][y - 1];
                        dp[k][x][y] %= mod;
                    }
                    if (j + 1 < n) {
                        dp[k][x][y] += dp[k - 1][x][y + 1];
                        dp[k][x][y] %= mod;
                    }
                }
            }
        }
        return dp[N - 1][i][j];
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({1,7,11});
    vector<int> vb({2,4,7});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({{0,0,1,1}, {1,0,1,0}, {1,1,0,0}});
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(4,3));
    fuxk.push_back(make_pair(2,3));
    fuxk.push_back(make_pair(2,1));
    fuxk.push_back(make_pair(5,0));
    
    s.findPaths(1, 3, 3, 0, 1);
}
