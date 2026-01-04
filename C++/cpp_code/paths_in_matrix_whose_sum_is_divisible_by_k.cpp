/*
https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/description/
2435. Paths in Matrix Whose Sum Is Divisible by K

You are given a 0-indexed m x n integer matrix grid and an integer k. You are currently at position (0, 0) and you want
to reach position (m - 1, n - 1) moving only down or right.

Return the number of paths where the sum of the elements on the path is divisible by k. Since the answer may be very
large, return it modulo 109 + 7.



Example 1:


Input: grid = [[5,2,4],[3,0,5],[0,7,2]], k = 3
Output: 2
Explanation: There are two paths where the sum of the elements on the path is divisible by k.
The first path highlighted in red has a sum of 5 + 2 + 4 + 5 + 2 = 18 which is divisible by 3.
The second path highlighted in blue has a sum of 5 + 3 + 0 + 5 + 2 = 15 which is divisible by 3.
Example 2:


Input: grid = [[0,0]], k = 5
Output: 1
Explanation: The path highlighted in red has a sum of 0 + 0 = 0 which is divisible by 5.
Example 3:


Input: grid = [[7,3,4,9],[2,3,6,2],[2,3,7,0]], k = 1
Output: 10
Explanation: Every integer is divisible by 1 so the sum of the elements on every possible path is divisible by k.


Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 5 * 104
1 <= m * n <= 5 * 104
0 <= grid[i][j] <= 100
1 <= k <= 50
*/
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
using namespace std;

class Solution {
private:
    const int MOD = 1000000007;

public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        // prev stores the prefix sum of last row
        vector<vector<int>> prev(n, vector<int>(k, 0));
        int sum = 0;
        for (int col = 0; col < n; col++) {
            sum = (sum + grid[0][col]) % k;
            prev[col][sum] = 1;
        }

        sum = grid[0][0] % k;
        for (int i = 1; i < m; i++) {
            vector<vector<int>> curr(n, vector<int>(k, 0));
            sum = (sum + grid[i][0]) % k;
            curr[0][sum] = 1;

            for (int j = 1; j < n; j++) {
                int val = grid[i][j];
                for (int r = 0; r < k; r++) {
                    int nr = (r + val) % k;
                    // we can move to current spot from above or left
                    curr[j][nr] = (prev[j][r] + curr[j - 1][r]) % MOD;
                }
            }

            swap(prev, curr);
        }
        return prev[n - 1][0];
    }
};