/*
 Given a 01 matrix M, find the longest line of consecutive one in the matrix. The line could be horizontal, vertical, diagonal or anti-diagonal.
 Example:
 Input:
 [[0,1,1,0],
 [0,1,1,0],
 [0,0,0,1]]
 Output: 3
 Hint: The number of elements in the given matrix will not exceed 10,000.
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
#include <set>
using namespace std;

class Solution {
public:
    int longestLine(vector<vector<int>>& M) {
        int m = M.size();
        if (m == 0) {
            return 0;
        }
        int n = M[0].size();
        
        vector<int> col(n, 0);
        vector<int> diag(m + n, 0);
        vector<int> antiDiag(m + n, 0);
        
        int result = 0;
        for (int i = 0; i < m; i++) {
            int row = 0;
            for (int j = 0; j < n; j++) {
                if (M[i][j] == 1) {
                    row += 1;
                    col[j] += 1;
                    diag[i + j] += 1;
                    antiDiag[i - j + n] += 1;
                    
                    result = max(result, row);
                    result = max(result, col[j]);
                    result = max(result, diag[i + j]);
                    result = max(result, antiDiag[i - j + n]);
                }
                else {
                    row = 0;
                    col[j] = 0;
                    diag[i + j] = 0;
                    antiDiag[i - j + n] = 0;
                }
            }
        }
        return result;
    }
};
