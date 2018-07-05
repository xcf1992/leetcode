/*
 We have a two dimensional matrix A where each value is 0 or 1.
 
 A move consists of choosing any row or column, and toggling each value in that row or column: changing all 0s to 1s, and all 1s to 0s.
 
 After making any number of moves, every row of this matrix is interpreted as a binary number, and the score of the matrix is the sum of these numbers.
 
 Return the highest possible score.
 
 
 
 Example 1:
 
 Input: [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
 Output: 39
 Explanation:
 Toggled to [[1,1,1,1],[1,0,0,1],[1,1,1,1]].
 0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
 
 
 Note:
 
 1 <= A.length <= 20
 1 <= A[0].length <= 20
 A[i][j] is 0 or 1.

 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

class Solution {
private:
    int countSum(vector<vector<int>>& A, int m, int n) {
        int result = 0;
        for (int i = 0; i < m; i++) {
            int row = 0;
            for (int j = 0; j < n; j++) {
                if (A[i][j] == 1) {
                    row += (1 << (n - j - 1));
                }
            }
            result += row;
        }
        return result;
    }
public:
    int matrixScore(vector<vector<int>>& A) {
        int m = A.size();
        int n = A[0].size();
        
        for (int i = 0; i < m; i++) {
            if (A[i][0] == 0) {
                for (int j = 0; j < n; j++) {
                    A[i][j] = 1 - A[i][j];
                }
            }
        }
        
        for (int j = 1; j < n; j++) {
            int countOne = 0;
            for (int i = 0; i < m; i++) {
                countOne += A[i][j];
            }
            
            if (countOne < m - countOne) {
                for (int i = 0; i < m; i++) {
                    A[i][j] = 1 - A[i][j];
                }
            }
        }
        return countSum(A, m, n);
    }
};
