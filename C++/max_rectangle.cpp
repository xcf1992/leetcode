#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
        if (matrix.empty()) {
            return 0;
        }
        int m = matrix.size();
        int n = matrix[0].size();
        
        vector<int> row(n, 0);
        vector<vector<int>> auxL(m, row);
        vector<vector<int>> auxW(m, row);
        
        auxL[0][0] = matrix[0][0];
        auxW[0][0] = matrix[0][0];
        int result = matrix[0][0];
        for (int i = 1; i < m; i++) {
            if (matrix[i][0] == '1') {
                auxL[i][0] = 1;
                auxW[i][0] = 1 + auxW[i - 1][0];
                result = max(result, auxL[i][0] * auxW[i][0]);
            }
        }
        
        for (int j = 1; j < n; j++) {
            if (matrix[0][j] == '1') {
                auxL[0][j] = 1 + auxL[0][j - 1];
                auxW[0][j] = 1;
                result = max(result, auxL[0][j] * auxW[0][j]);
            }
        }
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == '1') {
                    auxL[i][j] = min(auxL[i][j - 1], min(auxL[i - 1][j], auxL[i - 1][j - 1])) + 1;
                    auxW[i][j] = min(auxW[i][j - 1], min(auxW[i - 1][j], auxW[i - 1][j - 1])) + 1;
                    result = max(result, auxL[i][j] * auxW[i][j]);
                }
            }
        }
        
        return result;
    }
};

int main() {
	Solution s;
	vector<char> row(1, '0');
	vector<vector<char>> matrix(1, row);
	return s.maximalRectangle(matrix);
	return 0;
}