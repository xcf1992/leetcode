/*
1289. Minimum Falling Path Sum II
https://leetcode.com/problems/minimum-falling-path-sum-ii/

Given a square grid of integers arr,
a falling path with non-zero shifts is a choice of exactly one element from each row of arr,
such that no two elements chosen in adjacent rows are in the same column.

Return the minimum sum of a falling path with non-zero shifts.

Example 1:
Input: arr = [[1,2,3],[4,5,6],[7,8,9]]
Output: 13
Explanation:
The possible falling paths are:
[1,5,9], [1,5,7], [1,6,7], [1,6,8],
[2,4,8], [2,4,9], [2,6,7], [2,6,8],
[3,4,8], [3,4,9], [3,5,7], [3,5,9]
The falling path with the smallest sum is [1,5,7], so the answer is 13.

Constraints:
1 <= arr.length == arr[i].length <= 200
-99 <= arr[i][j] <= 99
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
#include <map>
#include <numeric>

using namespace std;
/*
when we update the least val and col,
we need to first assign current least val and col to less val and col
same as 265. Paint House II
*/
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& arr) {
        int m = arr.size();
        if (m == 0) {
            return 0;
        }
        int n = arr[0].size();

        int leastVal = INT_MAX;
        int leastCol = -1;
        int lessVal = INT_MAX;
        int lessCol = -1;
        for (int j = 0; j < n; ++j) {
            if (arr[0][j] < leastVal) {
                lessVal = leastVal;
                leastVal = arr[0][j];
                lessCol = leastCol;
                leastCol = j;
            } else if (arr[0][j] < lessVal) {
                lessVal = arr[0][j];
                lessCol = j;
            }
        }

        for (int i = 1; i < m; ++i) {
            int newLeastVal = INT_MAX;
            int newLeastCol = -1;
            int newLessVal = INT_MAX;
            int newLessCol = -1;
            for (int j = 0; j < n; ++j) {
                int sum = arr[i][j];
                if (j != leastCol) {
                    sum += leastVal;
                } else {
                    sum += lessVal;
                }

                if (sum < newLeastVal) {
                    newLessVal = newLeastVal;
                    newLeastVal = sum;
                    newLessCol = newLeastCol;
                    newLeastCol = j;
                } else if (sum < newLessVal) {
                    newLessVal = sum;
                    newLessCol = j;
                }
            }
            leastVal = newLeastVal;
            leastCol = newLeastCol;
            lessVal = newLessVal;
            lessCol = newLessCol;
        }
        return leastVal;
    }
};