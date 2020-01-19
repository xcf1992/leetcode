/*
363. Max Sum of Rectangle No Larger Than K

Given a non-empty 2D matrix matrix and an integer k,
find the max sum of a rectangle in the matrix such that its sum is no larger than k.

Example:
Input: matrix = [[1,0,1],[0,-2,3]], k = 2
Output: 2
Explanation: Because the sum of rectangle [[0, 1], [-2, 3]] is 2,
and 2 is the max number no larger than k (k = 2).

Note:
The rectangle inside the matrix must have an area > 0.
What if the number of rows is much larger than the number of columns?
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
#include <stdio.h>
#include <map>
#include <set>
#include <numeric>
using namespace std;
/*
Logic : loop for l and col range for column. Now iterate through the rows and add cur_sum to the set.
and as we need sum<=k or cur_sum[j]-cur_sum[i]<=k or cur_sum[j]-k<=cur_sum[i].
For this we can use set and keep updating the ans if we get any better ans not greater than k.
Complexity - Time - O(mmlog(n))
Space - O(n)
*/
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m = matrix.size();
        if (m == 0) {
            return 0;
        }
        int n = matrix[0].size();

        int result = INT_MIN;
        // the top left point of the rectangel will be looped from matrix[0][0] ... matrix[0][n - 1]
        for (int l = 0; l < n; l++) {
            // row sum i stores the sum for row i from position l to col inclusive
            vector<int> rowSum(m, 0);
            for (int col = l; col < n; col++) {
                for (int i = 0; i < m; i++) {
                    rowSum[i] += matrix[i][col];
                }
                // curSum stores the sum of rowSum from row 0 to cur row inclusive
                // thus sum of rectangle from topleft [0][l] to botright [curRow][col]
                set<int> s;
                s.insert(0);
                int curSum = 0;
                for (int row : rowSum) {
                    curSum += row;
                    auto it = s.lower_bound(curSum - k);
                    // *it >= curSum - k --> curSum - *it <= k
                    if (it != s.end()) {
                        // curSum - *it, its sum of cur full rectangle desc above and remove an above part
                        result = max(result, curSum - *it);
                    }
                    s.insert(curSum);
                }
            }
        }
        return result;
    }
};
