/*
766. Toeplitz Matrix
A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same element.

Now given an M x N matrix, return True if and only if the matrix is Toeplitz.


Example 1:

Input:
matrix = [
  [1,2,3,4],
  [5,1,2,3],
  [9,5,1,2]
]
Output: True
Explanation:
In the above grid, the diagonals are:
"[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]".
In each diagonal all elements are the same, so the answer is True.
Example 2:

Input:
matrix = [
  [1,2],
  [2,2]
]
Output: False
Explanation:
The diagonal "[1, 2]" has different elements.

Note:

matrix will be a 2D array of integers.
matrix will have a number of rows and columns in range [1, 20].
matrix[i][j] will be integers in range [0, 99].

Follow up:

What if the matrix is stored on disk,
and the memory is limited such that you can only load at most one row of the matrix into the memory at once?

What if the matrix is so large that you can only load up a partial row into the memory at once?
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
using namespace std;

class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++)
                if (matrix[i][j] != matrix[i - 1][j - 1]) {
                    return false;
                }
        }
        return true;
    }
};

/*
For the follow-up 1,
we are only able to load one row at one time,
so we have to use a buffer (1D data structure) to store the row info.
When next row comes as a streaming flow,
we can compare each value (say, matrix[i][j], i>=1, j>=1) to the "upper-left" value in the buffer (buffer[j - 1]);
meanwhile,
we update the buffer by inserting the 1st element of the current row (matrix[i][0]) to buffer at position 0 (buffer[0]),
and removing the last element in the buffer.

For the follow-up 2,
we can only load a partial row at one time.
We could split the whole matrix vertically into several sub-matrices,
while each sub-matrix should have one column overlapped.
We repeat the same method in follow-up 1 for each sub-matrix.

For example:

[1 2 3 4 5 6 7 8 9 0]              [1 2 3 4]              [4 5 6 7]              [7 8 9 0]
[0 1 2 3 4 5 6 7 8 9]              [0 1 2 3]              [3 4 5 6]              [6 7 8 9]
[1 0 1 2 3 4 5 6 7 8]     -->      [1 0 1 2]       +      [2 3 4 5]       +      [5 6 7 8]
[2 1 0 1 2 3 4 5 6 7]              [2 1 0 1]              [1 2 3 4]              [4 5 6 7]
[3 2 1 0 1 2 3 4 5 6]              [3 2 1 0]              [0 1 2 3]              [3 4 5 6]
*/