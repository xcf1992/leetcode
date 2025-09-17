/*
1659. Maximize Grid Happiness
https://leetcode.com/problems/maximize-grid-happiness/

You are given four integers, m, n, introvertsCount,
and extrovertsCount. You have an m x n grid,
and there are two types of people: introverts and extroverts.
There are introvertsCount introverts and extrovertsCount extroverts.

You should decide how many people you want to live in the grid and assign each of them one grid cell.
Note that you do not have to have all the people living in the grid.

The happiness of each person is calculated as follows:
Introverts start with 120 happiness and lose 30 happiness for each neighbor (introvert or extrovert).
Extroverts start with 40 happiness and gain 20 happiness for each neighbor (introvert or extrovert).
Neighbors live in the directly adjacent cells north, east, south, and west of a person's cell.
The grid happiness is the sum of each person's happiness. Return the maximum possible grid happiness.

Example 1:
Input: m = 2, n = 3, introvertsCount = 1, extrovertsCount = 2
Output: 240
Explanation: Assume the grid is 1-indexed with coordinates (row, column).
We can put the introvert in cell (1,1) and put the extroverts in cells (1,3) and (2,3).
- Introvert at (1,1) happiness: 120 (starting happiness) - (0 * 30) (0 neighbors) = 120
- Extrovert at (1,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
- Extrovert at (2,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
The grid happiness is 120 + 60 + 60 = 240.
The above figure shows the grid in this example with each person's happiness. The introvert stays in the light green cell while the extroverts live on the light purple cells.

Example 2:
Input: m = 3, n = 1, introvertsCount = 2, extrovertsCount = 1
Output: 260
Explanation: Place the two introverts in (1,1) and (3,1) and the extrovert at (2,1).
- Introvert at (1,1) happiness: 120 (starting happiness) - (1 * 30) (1 neighbor) = 90
- Extrovert at (2,1) happiness: 40 (starting happiness) + (2 * 20) (2 neighbors) = 80
- Introvert at (3,1) happiness: 120 (starting happiness) - (1 * 30) (1 neighbor) = 90
The grid happiness is 90 + 80 + 90 = 260.

Example 3:
Input: m = 2, n = 2, introvertsCount = 4, extrovertsCount = 0
Output: 240

Constraints:
1 <= m, n <= 5
0 <= introvertsCount, extrovertsCount <= min(m * n, 6)
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
#include <cfloat>
#include <stdio.h>
#include <map>
#include <set>
#include <list>
#include <numeric>
#include <random>
#include <vector>
#include "extra_data_types.hpp"
using namespace std;
/*
OK, tracking people in the grid is costly, and you will get TLE if you do not use memoisation.

I saw several solutions that cheat on large test cases.

Fortunately, to calculate the happiness balance - how placing a person subtracts or adds to the overall happiness - we only need to know last m cells we processed.

We can use bit masks to track introverts and extroverts in the last m cells, and shift them as we go. Thus, we have here 5D DP:

Position in the grid (p = i * m + j) -> up to 25.
Remaining introverts -> up to 6.
Remaining extroverts -> up to 6.
Introverts mask -> up to 2 ^ (m + 1) - 1 = 63 combinations.
Extroverts mask -> up to 2 ^ (m + 1) - 1 = 63 combinations.
*/
class Solution
{
public:
    int dp[25][7][7][64][64] = {};
    int nCost(int m, int n, int i, int j, int mask_in, int mask_ex, int d)
    {
        int diff = 0, up = (1 << (n - 1));
        if (j > 0 && (mask_in & 1))
            diff += d - 30;
        if (i > 0 && (mask_in & up))
            diff += d - 30;
        if (j > 0 && (mask_ex & 1))
            diff += d + 20;
        if (i > 0 && (mask_ex & up))
            diff += d + 20;
        return diff;
    }
    int dfs(int m, int n, int p, int in, int ex, int mask_in, int mask_ex)
    {
        int i = p / n, j = p % n;
        if (i >= m)
            return 0;
        if (dp[p][in][ex][mask_in][mask_ex])
            return dp[p][in][ex][mask_in][mask_ex] - 1;
        int n_mask_in = (mask_in << 1) & 63, n_mask_ex = (mask_ex << 1) & 63;
        int res = dfs(m, n, p + 1, in, ex, n_mask_in, n_mask_ex);
        if (in > 0)
        {
            int diff = 120 + nCost(m, n, i, j, mask_in, mask_ex, -30);
            res = max(res, diff + dfs(m, n, p + 1, in - 1, ex, n_mask_in + 1, n_mask_ex));
        }
        if (ex > 0)
        {
            int diff = 40 + nCost(m, n, i, j, mask_in, mask_ex, 20);
            res = max(res, diff + dfs(m, n, p + 1, in, ex - 1, n_mask_in, n_mask_ex + 1));
        }
        dp[p][in][ex][mask_in][mask_ex] = res + 1;
        return res;
    }
    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount)
    {
        return dfs(m, n, 0, introvertsCount, extrovertsCount, 0, 0);
    }
};
