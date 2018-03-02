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
    int update(vector<vector<int>>& matrix, vector<vector<int>>& dp) {
        int m = matrix.size();
        int n = matrix[0].size();
        int result = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (j - 1 >= 0 && dp[i][j] > dp[i][j - 1]) {
                    dp[i][j] = max(dp[i][j], dp[i][j - 1] + 1);
                }
                
                if (i - 1 >= 0 && dp[i][j] > dp[i - 1][j]) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j] + 1);
                }
                
                if (j + 1 < n && dp[i][j] > dp[i][j + 1]) {
                    dp[i][j] = max(dp[i][j], dp[i][j + 1] + 1);
                }
                
                if (i + 1 < m && dp[i][j] > dp[i + 1][j]) {
                    dp[i][j] = max(dp[i][j], dp[i + 1][j] + 1);
                }
                result = max(result, dp[i][j]);
            }
        }
        return result;
    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) {
            return 0;
        }
        int n = matrix[0].size();
        
        vector<vector<int>> dp(m, vector<int>(n, 1));
        int result = 0;
        while (true) {
            int temp = update(matrix, dp);
            if (temp > result) {
                result = temp;
            }
            else {
                break;
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
    vector<vector<int>> matrix({{9,9,4},{6,7,8},{2,1,1}});
    
    s.longestIncreasingPath(matrix);
}
