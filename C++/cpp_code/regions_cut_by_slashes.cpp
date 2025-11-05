/*
959. Regions Cut By Slashes
In a N x N grid composed of 1 x 1 squares,
each 1 x 1 square consists of a /, \, or blank space.
These characters divide the square into contiguous regions.

(Note that backslash characters are escaped, so a \ is represented as "\\".)

Return the number of regions.

Example 1:

Input:
[
" /",
"/ "
]
Output: 2
Explanation: The 2x2 grid is as follows:

Example 2:

Input:
[
" /",
"  "
]
Output: 1
Explanation: The 2x2 grid is as follows:

Example 3:

Input:
[
"\\/",
"/\\"
]
Output: 4
Explanation: (Recall that because \ characters are escaped, "\\/" refers to \/, and "/\\" refers to /\.)
The 2x2 grid is as follows:

Example 4:

Input:
[
"/\\",
"\\/"
]
Output: 5
Explanation: (Recall that because \ characters are escaped, "/\\" refers to /\, and "\\/" refers to \/.)
The 2x2 grid is as follows:

Example 5:

Input:
[
"//",
"/ "
]
Output: 3
Explanation: The 2x2 grid is as follows:

Note:

1 <= grid.length == grid[0].length <= 30
grid[i][j] is either '/', '\', or ' '.
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
#include <numeric>
using namespace std;
/*
Split a cell in to 4 parts like this.
We give it a number top is 1, right is 2, bottom is 3 left is 4.

Two adjacent parts in different cells are contiguous regions.
In case '/', top and left are contiguous, botton and right are contiguous.
In case '\\', top and right are contiguous, bottom and left are contiguous.
In case ' ', all 4 parts are contiguous.

Congratulation.
Now you have another problem of counting the number of islands.

DFS will be good enough to solve it.
As I did in 947.Most Stones Removed with Same Row or Column
I solve it with union find.

Good luck and have fun.

Time Complexity:
O(N^2)
*/
class Solution {
private:
    int count = 0;
    int n = 0;

    int find(int x, vector<int> &parent) {
        return parent[x] == -1 ? x : find(parent[x], parent);
    }

    void unin(int x, int y, vector<int> &parent) {
        int px = find(x, parent);
        int py = find(y, parent);
        if (px != py) {
            count -= 1;
            parent[px] = py;
        }
    }

    int index(int i, int j, int k) {
        return (i * n + j) * 4 + k;
    }

public:
    int regionsBySlashes(vector<string> &grid) {
        n = grid.size();
        count = n * n * 4;
        vector<int> parent(count, -1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                /*
                        0
                    3       1
                        2
               */
                if (i > 0) {
                    unin(index(i - 1, j, 2), index(i, j, 0), parent);
                }

                if (j > 0) {
                    unin(index(i, j - 1, 1), index(i, j, 3), parent);
                }

                if (grid[i][j] != '/') {
                    unin(index(i, j, 2), index(i, j, 3), parent);
                    unin(index(i, j, 0), index(i, j, 1), parent);
                }

                if (grid[i][j] != '\\') {
                    unin(index(i, j, 1), index(i, j, 2), parent);
                    unin(index(i, j, 0), index(i, j, 3), parent);
                }
            }
        }
        return count;
    }
};