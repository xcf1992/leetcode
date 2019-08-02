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
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution { // dp
private:
    bool isPerfectSquare(int n1, int n2) {
        int root = sqrt(n1 + n2);
        return root * root == n1 + n2;
    }
public:
    int numSquarefulPerms(vector<int>& A) {
        int n = A.size();
        vector<vector<int>> adj;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) if (isPerfectSquare(A[i], A[j])) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }

        vector<vector<int>> dp(1 << n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            dp[1 << i][i] = 1;
        }

        for (int state = 3; state < (1 << n); ++state) {
            for (int i = 0; i < n; ++i) if (state & (1 << i)) {
                for (int j : adj[i]) if (state & (1 << j)) {
                    dp[state][i] += dp[state ^ (1 << i)][j];
                }
            }
        }

        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += dp[(1 << n) - 1][i];
        }

        /** Divide out permutations of equal elements. */
        for (int i = 0; i < n; i++) {
            int k = 1;
            for (int j = i + 1; j < n; j++) {
                if (A[i] == A[j]) {
                    k++;
                }
            }
            result /= k;
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({1,17,8});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {0,1},
        {1,2},
        {2,1},
        {1,0},
        {0,2},
        {0,0},
        {1,1}
    });
    vector<vector<int>> matrix2({
        {1,2,2,3,5},
        {3,2,3,4,4},
        {2,4,5,3,1},
        {6,7,1,4,5},
        {5,1,1,2,4}
    });
    vector<string> words({"hot","dot","dog","lot","log","cog"});
    TreeNode* r1 = new TreeNode(0);
    TreeNode* r2 = new TreeNode(1);
    TreeNode* r3 = new TreeNode(3);
    r1 -> left = r2;
    s.numSquarefulPerms(temp);
}
