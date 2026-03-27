/*
https://leetcode.com/problems/get-biggest-three-rhombus-sums-in-a-grid/description/
1878. Get Biggest Three Rhombus Sums in a Grid

You are given an m x n integer matrix grid​​​.

A rhombus sum is the sum of the elements that form the border of a regular rhombus shape in grid​​​. The rhombus
must have the shape of a square rotated 45 degrees with each of the corners centered in a grid cell. Below is an image
of four valid rhombus shapes with the corresponding colored cells that should be included in each rhombus sum:


Note that the rhombus can have an area of 0, which is depicted by the purple rhombus in the bottom right corner.

Return the biggest three distinct rhombus sums in the grid in descending order. If there are less than three distinct
values, return all of them.



Example 1:


Input: grid = [[3,4,5,1,3],[3,3,4,2,3],[20,30,200,40,10],[1,5,5,4,1],[4,3,2,2,5]]
Output: [228,216,211]
Explanation: The rhombus shapes for the three biggest distinct rhombus sums are depicted above.
- Blue: 20 + 3 + 200 + 5 = 228
- Red: 200 + 2 + 10 + 4 = 216
- Green: 5 + 200 + 4 + 2 = 211
Example 2:


Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
Output: [20,9,8]
Explanation: The rhombus shapes for the three biggest distinct rhombus sums are depicted above.
- Blue: 4 + 2 + 6 + 8 = 20
- Red: 9 (area 0 rhombus in the bottom right corner)
- Green: 8 (area 0 rhombus in the bottom middle)
Example 3:

Input: grid = [[7,7,7]]
Output: [7]
Explanation: All three possible rhombus sums are the same, so return [7].


Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 50
1 <= grid[i][j] <= 105
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
#include <set>
using namespace std;
/*
Intuition
A rhombus in the grid is a square rotated by 45°, and we are required to compute the sum of only the border cells of
such shapes.

Important observations:

A rhombus of size 0 consists of just one cell.
For a rhombus of size k with the top vertex at (i, j):
Right vertex → (i + k, j + k)
Bottom vertex → (i + 2k, j)
Left vertex → (i + k, j - k)
These four vertices must lie inside the grid.
To solve the problem, we generate all possible rhombus shapes starting from every cell, compute their border sums, and
keep only distinct values. Finally, we return the largest three sums in descending order.

Approach
Let m and n be the number of rows and columns of the grid.
Iterate through every cell (i, j) treating it as the top vertex of a rhombus.
Insert the size 0 rhombus sum (the value of the cell itself).
For increasing rhombus size k:
Compute the coordinates of the right, bottom, and left vertices.
If any of these coordinates go outside the grid, stop expanding.
If the rhombus is valid, compute the border sum by traversing the four edges:
Top → Right
Right → Bottom
Bottom → Left
Left → Top
Store every computed sum in a set to ensure distinct values.
After processing the entire grid, extract the largest three values from the set.
 */
class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        set<int> st;

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {

                // size 0 rhombus
                st.insert(grid[i][j]);

                for(int k = 1; ; k++) {

                    int r = i + 2*k;
                    int left = j - k;
                    int right = j + k;

                    if(r >= m || left < 0 || right >= n) break;

                    int sum = 0;

                    int x = i, y = j;

                    // top -> right
                    for(int t = 0; t < k; t++) {
                        sum += grid[x + t][y + t];
                    }

                    // right -> bottom
                    for(int t = 0; t < k; t++) {
                        sum += grid[x + k + t][y + k - t];
                    }

                    // bottom -> left
                    for(int t = 0; t < k; t++) {
                        sum += grid[x + 2*k - t][y - t];
                    }

                    // left -> top
                    for(int t = 0; t < k; t++) {
                        sum += grid[x + k - t][y - k + t];
                    }

                    st.insert(sum);
                }
            }
        }

        vector<int> ans;
        for(auto it = st.rbegin(); it != st.rend() && ans.size() < 3; ++it) {
            ans.push_back(*it);
        }

        return ans;
    }
};
