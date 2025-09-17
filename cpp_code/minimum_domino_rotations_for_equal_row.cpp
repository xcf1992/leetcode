/*
1007. Minimum Domino Rotations For Equal Row
https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/

In a row of dominoes,
A[i] and B[i] represent the top and bottom halves of the i-th domino.
(A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)

We may rotate the i-th domino, so that A[i] and B[i] swap values.
Return the minimum number of rotations so that all the values in A are the same, or all the values in B are the same.
If it cannot be done, return -1.

Example 1:
Input: A = [2,1,2,4,2,2], B = [5,2,6,2,3,2]
Output: 2
Explanation:
The first figure represents the dominoes as given by A and B: before we do any rotations.
If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.

Example 2:
Input: A = [3,5,1,2,3], B = [3,6,3,3,4]
Output: -1
Explanation:
In this case, it is not possible to rotate the dominoes to make one row of values equal.

Note:
1 <= A[i], B[i] <= 6
2 <= A.length == B.length <= 20000
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
Algorithm

Pick up the first element. It has two sides: A[0] and B[0].

Check if one could make all elements in A row or B row to be equal to A[0].
If yes, return the minimum number of rotations needed.

Check if one could make all elements in A row or B row to be equal to B[0].
If yes, return the minimum number of rotations needed.

Otherwise return -1.
*/
class Solution {
public:
    int minDominoRotations(vector<int>& A, vector<int>& B) {
        int n = A.size();
        for (int i = 0, a = 0, b = 0; i < n; ++i) {
            if (A[i] != A[0] and B[i] != A[0]) {
                break;
            }

            if (A[i] != A[0]) {
                a += 1;
            }
            if (B[i] != A[0]) {
                b += 1;
            }
            if (i == n - 1) {
                return min(a, b);
            }
        }

        for (int i = 0, a = 0, b = 0; i < n; ++i) {
            if (A[i] != B[0] and B[i] != B[0]) {
                break;
            }
            if (A[i] != B[0]) {
                a += 1;
            }
            if (B[i] != B[0]) {
                b += 1;
            }
            if (i == n - 1) {
                return min(a, b);
            }
        }
        return -1;
    }
};
