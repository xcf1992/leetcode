/*
 1031. Number of Enclaves
 Given a 2D array A, each cell is 0 (representing sea) or 1 (representing land)
 
 A move consists of walking from one land square 4-directionally to another land square, or off the boundary of the grid.
 
 Return the number of land squares in the grid for which we cannot walk off the boundary of the grid in any number of moves.
 
 
 
 Example 1:
 
 Input: [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
 Output: 3
 Explanation:
 There are three 1s that are enclosed by 0s, and one 1 that isn't enclosed because its on the boundary.
 Example 2:
 
 Input: [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
 Output: 0
 Explanation:
 All 1s are either on the boundary or can reach the boundary.
 
 
 Note:
 
 1 <= A.length <= 500
 1 <= A[i].length <= 500
 0 <= A[i][j] <= 1
 All rows have the same size.
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
    int M = 0;
    int N = 0;
    
    bool canPass(int row, int col, int& count, vector<vector<int>>& A) {
        if (row < 0 or col < 0 or row >= M or col >= N) {
            return true;
        }
        
        if (A[row][col] != 1) {
            return false;
        }
        
        count += 1;
        A[row][col] = 2;
        return canPass(row + 1, col, count, A) || canPass(row - 1, col, count, A) ||
            canPass(row, col + 1, count, A) || canPass(row, col - 1, count, A);
    }
public:
    int numEnclaves(vector<vector<int>>& A) {
        int result = 0;
        M = A.size();
        N = A[0].size();
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[i][j] == 1) {
                    int count = 0;
                    if (!canPass(i, j, count, A)) {
                        result += count;
                    }
                }
            }
        }
        return result;
    }
};
