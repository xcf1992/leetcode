/*
59. Spiral Matrix II
https://leetcode.com/problems/spiral-matrix-ii/

Given a positive integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

Example:
Input: 3
Output:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
private:
    vector<vector<int>> diff{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> result(n, vector<int>(n, 0));
        vector<int> steps{n, n - 1};  // steps we can take during current move
        int direction = 0;            // index of direction.
        int curR = 0;
        int curC = -1;  // initial position
        int num = 1;
        while (steps[direction % 2] > 0) {
            for (int i = 0; i < steps[direction % 2]; ++i) {
                curR += diff[direction][0];
                curC += diff[direction][1];
                result[curR][curC] = num;
                num += 1;
            }
            steps[direction % 2] -= 1;
            direction = (direction + 1) % 4;
        }
        return result;
    }
};