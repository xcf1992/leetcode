/*
54. Spiral Matrix
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

Example 1:

Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output: [1,2,3,6,9,8,7,4,5]
Example 2:

Input:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]

*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
private:
    vector<vector<int> > dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) {
            return {};
        }
        int n = matrix[0].size();

        vector<int> steps{n, m - 1}; // steps we can take during current move
        int direction = 0;   // index of direction.
        int curR = 0;
        int curC = -1;    // initial position
        vector<int> result;
        while (steps[direction % 2] > 0) {
            for (int i = 0; i < steps[direction % 2]; ++i) {
                curR += dirs[direction][0];
                curC += dirs[direction][1];
                result.push_back(matrix[curR][curC]);
            }
            steps[direction % 2] -= 1;
            direction = (direction + 1) % 4;
        }
        return result;
    }
};
