/*
1420. Build Array Where You Can Find The Maximum Exactly K Comparisons
https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/

Given three integers n, m and k.
Consider the following algorithm to find the maximum element of an array of positive integers:

max_val= -1;
max_idx = -1;
search_cost = 0;
n = arr.length;
for (int i = 0; i < n; ++i) {
    if (max_val < arr[i]) {
        max_val = arr[i];
        max_idx = i;
        search_cost += 1;
    }
}
return max_idx;

You should build the array arr which has the following properties:
arr has exactly n integers.
1 <= arr[i] <= m where (0 <= i < n).
After applying the mentioned algorithm to arr, the value search_cost is equal to k.
Return the number of ways to build the array arr under the mentioned conditions. As the answer may grow large, the
answer must be computed modulo 10^9 + 7.

Example 1:
Input: n = 2, m = 3, k = 1
Output: 6
Explanation: The possible arrays are [1, 1], [2, 1], [2, 2], [3, 1], [3, 2] [3, 3]

Example 2:
Input: n = 5, m = 2, k = 3
Output: 0
Explanation: There are no possible arrays that satisify the mentioned conditions.

Example 3:
Input: n = 9, m = 1, k = 1
Output: 1
Explanation: The only possible array is [1, 1, 1, 1, 1, 1, 1, 1, 1]

Example 4:
Input: n = 50, m = 100, k = 25
Output: 34549172
Explanation: Don't forget to compute the answer modulo 1000000007

Example 5:
Input: n = 37, m = 17, k = 7
Output: 418930126

Constraints:
1 <= n <= 50
1 <= m <= 100
0 <= k <= n
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
#include <set>
#include <climits>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    /* let ways[i][j][k] = # ways to construct an array of length i with max element equal to j and a search cost of k.
     */
    long long ways[51][101][51];
    const int MOD = 1e9 + 7;

    int numOfArrays(int n, int m, int k) {
        memset(ways, 0, sizeof(ways));

        /*
        There are our base cases. For each index 1 <= j <= m,
        we require ways[1][j][1] = 1 because the array consisting of only the element j
        has length 1, maximum element j, and it has a search cost of 1.
        */
        for (int j = 1; j <= m; j++) {
            ways[1][j][1] = 1;
        }

        for (int a = 1; a <= n; a++) {
            for (int b = 1; b <= m; b++) {
                for (int c = 1; c <= k; c++) {
                    long long s = 0;
                    /* In this first case, we can append any element from [1, b] to the end of the array. */
                    s = (s + b * ways[a - 1][b][c]) % MOD;
                    /* In this second case, we can append the element "b" to the end of the array. */
                    for (int x = 1; x < b; x++) {
                        s = (s + ways[a - 1][x][c - 1]) % MOD;
                    }
                    ways[a][b][c] = (ways[a][b][c] + s) % MOD;
                }
            }
        }

        long long ans = 0;
        for (int j = 1; j <= m; j++) {
            ans = (ans + ways[n][j][k]) % MOD;
        }
        return ans;
    }
};
