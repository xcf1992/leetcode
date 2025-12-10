/*
1504. Count Submatrices With All Ones
https://leetcode.com/problems/count-submatrices-with-all-ones/

Given a rows * columns matrix mat of ones and zeros,
return how many submatrices have all ones.

Example 1:
Input: mat = [[1,0,1],
              [1,1,0],
              [1,1,0]]
Output: 13
Explanation:
There are 6 rectangles of side 1x1.
There are 2 rectangles of side 1x2.
There are 3 rectangles of side 2x1.
There is 1 rectangle of side 2x2.
There is 1 rectangle of side 3x1.
Total number of rectangles = 6 + 2 + 3 + 1 + 1 = 13.

Example 2:
Input: mat = [[0,1,1,0],
              [0,1,1,1],
              [1,1,1,0]]
Output: 24
Explanation:
There are 8 rectangles of side 1x1.
There are 5 rectangles of side 1x2.
There are 2 rectangles of side 1x3.
There are 4 rectangles of side 2x1.
There are 2 rectangles of side 2x2.
There are 2 rectangles of side 3x1.
There is 1 rectangle of side 3x2.
Total number of rectangles = 8 + 5 + 2 + 4 + 2 + 2 + 1 = 24.

Example 3:
Input: mat = [[1,1,1,1,1,1]]
Output: 21

Example 4:
Input: mat = [[1,0,1],[0,1,0],[1,0,1]]
Output: 5

Constraints:
1 <= rows <= 150
1 <= columns <= 150
0 <= mat[i][j] <= 1
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <climits>

using namespace std;

// https://leetcode.com/problems/count-submatrices-with-all-ones/discuss/720265/Java-Detailed-Explanation-From-O(MNM)-to-O(MN)-by-using-Stack
class Solution {
private:
    int m = 0;
    int n = 0;

    int check(vector<int>& height) {
        vector<int> count(n, 0);
        vector<int> stk;
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() and height[stk.back()] >= height[i]) {
                stk.pop_back();
            }

            if (!stk.empty()) {
                int pre = stk.back();
                count[i] = count[pre] + height[i] * (i - pre);
            } else {
                count[i] = height[i] * (i + 1);
            }

            stk.push_back(i);
        }

        int sum = 0;
        for (int c : count) {
            sum += c;
        }
        return sum;
    }

public:
    int numSubmat(vector<vector<int>>& mat) {
        m = mat.size();
        n = mat[0].size();
        vector<int> height(n, 0);
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                height[j] = mat[i][j] == 0 ? 0 : height[j] + 1;
            }
            result += check(height);
        }
        return result;
    }
};