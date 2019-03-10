/*
 1007. Minimum Domino Rotations For Equal Row
 In a row of dominoes, A[i] and B[i] represent the top and bottom halves of the i-th domino.  (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)
 
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

class Solution {
private:
    int rotate(vector<int>& A, vector<int>& B) {
        bool aRow = true;
        int swap1 = 0;
        for (int i = 1; i < A.size() and aRow; i++) {
            if (A[i] == A[0]) {
                aRow = true;
            }
            else if (B[i] == A[0]) {
                swap1 += 1;
            }
            else {
                aRow = false;
            }
        }
        
        bool bRow = true;
        int swap2 = 0;
        for (int i = 1; i < B.size() and bRow; i++) {
            if (B[i] == B[0]) {
                bRow = true;
            }
            else if (A[i] == B[0]) {
                swap2 += 1;
            }
            else {
                bRow = false;
            }
        }
        if (aRow and bRow) {
            return min(swap1, swap2);
        }
        return aRow ? swap1 : (bRow ? swap2 : -1);
    }
public:
    int minDominoRotations(vector<int>& A, vector<int>& B) {
        int result1 = rotate(A, B);
        swap(A[0], B[0]);
        int result2 = rotate(A, B);
        if (result1 == -1) {
            if (result2 == -1) {
                return -1;
            }
            return result2 + 1;
        }
        if (result2 == -1) {
            return result1;
        }
        return min(result2 + 1, result1);
    }
};
