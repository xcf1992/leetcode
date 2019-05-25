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

class Solution {
private:
    int M = 0;
    int N = 0;
    
    bool search(int sRow, int sCol, int eRow, int eCol, vector<vector<int>>& matrix, int target) {
        if (sRow < 0 or sRow >= M or sCol < 0 or sCol >= N) {
            return false;
        }
        if (eRow < 0 or eRow >= M or eCol < 0 or eCol >= N) {
            return false;
        }
        if (sRow > eRow or sCol > eCol) {
            return false;
        }
        
        if (sRow == eRow and sCol == eCol) {
            return matrix[sRow][sCol] == target;
        }
        if (matrix[sRow][sCol] > target) {
            return false;
        }
        if (matrix[eRow][eCol] < target) {
            return false;
        }
        
        int mRow = sRow + (eRow - sRow) / 2;
        int mCol = sCol + (eCol - sCol) / 2;
        if (target == matrix[mRow][mCol]) {
            return true;
        }
        
        if (target < matrix[mRow][mCol]) {
            return search(sRow, sCol, mRow, mCol, matrix, target);
        }
        
        return search(mRow + 1, mCol + 1, eRow, eCol, matrix, target) or
        search(mRow + 1, sCol, eRow, mCol, matrix, target) or
        search(sRow, mCol + 1, mRow, eCol, matrix, target);
    }
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        M = matrix.size();
        if (M == 0) {
            return false;
        }
        N = matrix[0].size();
        
        return search(0, 0, M - 1, N - 1, matrix, target);
    }
};

int main() {
    int x = stoi("001");
    Solution s;
    vector<int> temp({1,10,100,1000});
    vector<vector<int>> matrix({
        {1,2,3,4,5},
        {6,7,8,9,10},
        {11,12,13,14,15},
        {16,17,18,19,20},
        {21,22,23,24,25}
    });
    s.searchMatrix(matrix, 5);
}
