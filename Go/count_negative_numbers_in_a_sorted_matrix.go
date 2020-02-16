/*
1351. Count Negative Numbers in a Sorted Matrix
https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/

Given a m * n matrix grid which is sorted in non-increasing order both row-wise and column-wise.
Return the number of negative numbers in grid.

Example 1:
Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
Output: 8
Explanation: There are 8 negatives number in the matrix.

Example 2:
Input: grid = [[3,2],[1,0]]
Output: 0

Example 3:
Input: grid = [[1,-1],[-1,-1]]
Output: 3

Example 4:
Input: grid = [[-1]]
Output: 1

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 100
-100 <= grid[i][j] <= 100
*/
package main

import (
    "fmt"
)
/*
This solution uses the fact that the negative regions of the matrix will form a "staircase" shape, e.g.:

++++++
++++--
++++--
+++---
+-----
+-----
What this solution then does is to "trace" the outline of the staircase.

Start from bottom-left corner of the matrix, count in the negative numers in each row.
*/
func countNegatives(grid [][]int) int {
    var m int = len(grid)
    var n int = len(grid[0])
    var result int = 0

    var row int = m - 1
    var col int = 0
    for row >= 0 && col < n {
        if grid[row][col] < 0 {
            row -= 1;
            result += n - col
        } else {
            col += 1
        }
    }
    return result
}
