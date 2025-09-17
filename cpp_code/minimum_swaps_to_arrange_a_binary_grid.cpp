/*
1536. Minimum Swaps to Arrange a Binary Grid
https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/

Given an n x n binary grid, in one step you can choose two adjacent rows of the grid and swap them.
A grid is said to be valid if all the cells above the main diagonal are zeros.

Return the minimum number of steps needed to make the grid valid, or -1 if the grid cannot be valid.
The main diagonal of a grid is the diagonal that starts at cell (1, 1) and ends at cell (n, n).

Example 1:
Input: grid = [[0,0,1],[1,1,0],[1,0,0]]
Output: 3

Example 2:
Input: grid = [[0,1,1,0],[0,1,1,0],[0,1,1,0],[0,1,1,0]]
Output: -1
Explanation: All rows are similar, swaps have no effect on the grid.

Example 3:
Input: grid = [[1,0,0],[1,1,0],[1,1,1]]
Output: 0

Constraints:
n == grid.length
n == grid[i].length
1 <= n <= 200
grid[i][j] is 0 or 1
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        const int n = grid.size();
        vector<int> tail0(n, 0); //t[i]: tailing zero count for i-th row
        for (int i = 0; i < n; i++) {
            for (int j = n - 1; j >= 0 and grid[i][j] == 0; --j) {
                tail0[i]++;
            }
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            int k = i;
            int req = n - 1 - i; // desired tailing zero count
            while (k < n and tail0[k] < req) {
                k++; // greedily find first swaping candidate and log the result into k. Note1
            }
            if (k == n) {
                return -1; // k is out of range. Fail in searching
            }

            //Core part of the question: moving up k-th row up, moving down [i, k-1
            //Part 1: move k-th row up to i-th row
            ans += k - i; // accumulate the operation cost of moving k to i

            //Part 2: move the rest involved row downward by offset 1
            while (k > i) { // simulate swaping operation of two adjacent rows in range of [i, k-1 ]
                tail0[k] = tail0[k-1];
                k--;
            }
        }
        return ans;
    }
};
/*Note 1: why dose greedy approach work?
Recall the row scanning is performed one by one from row 0, which ask most tailing 0;
Suppose, current row (i-th row) asks for a row with at least 4 zeros, and the neaerst downward row (j-th) has 5 tailing zeros. You can greedily but aslo safely choose it as candidate. any rows after than i-th row will ask for less than 4 tailing rows. So you greedy approach will cause no trouble at all.
*/
