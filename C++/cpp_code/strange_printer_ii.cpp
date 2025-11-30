/*
1591. Strange Printer II
https://leetcode.com/problems/strange-printer-ii/

There is a strange printer with the following two special requirements:
On each turn, the printer will print a solid rectangular pattern of a single color on the grid.
This will cover up the existing colors in the rectangle.
Once the printer has used a color for the above operation, the same color cannot be used again.
You are given a m x n matrix targetGrid, where targetGrid[row][col] is the color in the position (row, col) of the grid.
Return true if it is possible to print the matrix targetGrid, otherwise, return false.

Example 1:
Input: targetGrid = [[1,1,1,1],[1,2,2,1],[1,2,2,1],[1,1,1,1]]
Output: true

Example 2:
Input: targetGrid = [[1,1,1,1],[1,1,3,3],[1,1,3,4],[5,5,1,4]]
Output: true

Example 3:
Input: targetGrid = [[1,2,1],[2,1,2],[1,2,1]]
Output: false
Explanation: It is impossible to form targetGrid because it is not allowed to print the same color in different turns.

Example 4:
Input: targetGrid = [[1,1,1],[3,1,3]]
Output: false

Constraints:
m == targetGrid.length
n == targetGrid[i].length
1 <= m, n <= 60
1 <= targetGrid[row][col] <= 60
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
#include <climits>
#include <map>
using namespace std;
/*
Explanation
For each color, find its index of left most, top most, right most, bottom most point.
Then we need to paint this color from [top, left] to [bottom, right].

If in the rectangle, all the colors are either the same or 0,
we mark all of them to 0.

If we can mark the whole grid to 0, it means the target if printable.


Complexity
Time O(CCMN)
Space O(4C)
*/
using vi = vector<int>;

class Solution {
public:
    vector<vi> pos;

    bool isPrintable(vector<vector<int>>& arr) {
        int n = arr.size();
        int m = arr[0].size();
        pos = vector<vector<int>>(61, {n, m, 0, 0});
        unordered_set<int> colors;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                colors.insert(arr[i][j]);
                int c = arr[i][j];
                pos[c][0] = min(pos[c][0], i);
                pos[c][1] = min(pos[c][1], j);
                pos[c][2] = max(pos[c][2], i);
                pos[c][3] = max(pos[c][3], j);
            }
        }
        while (!colors.empty()) {
            unordered_set<int> colors2;
            for (int v : colors) {
                if (!test(v, arr)) {
                    colors2.insert(v);
                }
            }
            if (colors2.size() == colors.size()) {
                return false;
            }
            colors = colors2;
        }
        return true;
    }

    bool test(int c, vector<vi>& arr) {
        for (int i = pos[c][0]; i <= pos[c][2]; i++) {
            for (int j = pos[c][1]; j <= pos[c][3]; j++) {
                if (arr[i][j] > 0 && arr[i][j] != c) {
                    return false;
                }
            }
        }
        for (int i = pos[c][0]; i <= pos[c][2]; i++) {
            for (int j = pos[c][1]; j <= pos[c][3]; j++) {
                arr[i][j] = 0;
            }
        }
        return true;
    }
};