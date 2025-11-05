/*
1411. Number of Ways to Paint N × 3 Grid
https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/

You have a grid of size n x 3
and you want to paint each cell of the grid with exactly one of the three colours:
Red, Yellow or Green while making sure that no two adjacent cells have the same colour
(i.e no two cells that share vertical or horizontal sides have the same colour).

You are given n the number of rows of the grid.
Return the number of ways you can paint this grid.
As the answer may grow large, the answer must be computed modulo 10^9 + 7.

Example 1:
Input: n = 1
Output: 12
Explanation: There are 12 possible way to paint the grid as shown:

Example 2:
Input: n = 2
Output: 54

Example 3:
Input: n = 3
Output: 246

Example 4:
Input: n = 7
Output: 106494

Example 5:
Input: n = 5000
Output: 30228214

Constraints:
n == grid.length
grid[i].length == 3
1 <= n <= 5000
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
#include <stdio.h>
#include "extra_data_types.hpp"
using namespace std;
/*
Intuition
Classic dynamic programming problem.

Explanation
Two pattern for each row, 121 and 123.
121, the first color same as the third in a row.
123, one row has three different colors.

We consider the state of the first row,
pattern 121: 121, 131, 212, 232, 313, 323.
pattern 123: 123, 132, 213, 231, 312, 321.
So we initialize a121 = 6, a123 = 6.

We consider the next possible for each pattern:
Patter 121 can be followed by: 212, 213, 232, 312, 313
Patter 123 can be followed by: 212, 231, 312, 232

121 => three 121, two 123
123 => two 121, two 123

So we can write this dynamic programming transform equation:
b121 = a121 * 3 + a123 * 2
b123 = a121 * 2 + a123 * 2

We calculate the result iteratively
and finally return the sum of both pattern a121 + a123

Complexity
Time O(N), Space O(1)
Of course, we can do better.
O(logN) Time Solution

Well, I don't think it's required,
But still you can mention during interview,
(as a ciper code hinting that you are my follower).
*/
class Solution {
public:
    int numOfWays(int n) {
        long a121 = 6, a123 = 6;
        long mod = 1e9 + 7;
        for (int i = 1; i < n; ++i) {
            long b121 = a121 * 3 + a123 * 2;
            long b123 = a121 * 2 + a123 * 2;
            a121 = b121 % mod;
            a123 = b123 % mod;
        }
        return (a121 + a123) % mod;
    }
};