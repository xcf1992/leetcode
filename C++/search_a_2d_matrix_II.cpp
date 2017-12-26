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
using namespace std;


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (m == 0) {
            return false;
        }
        int n = matrix[0].size();
        
        int i = 0;
        int j = n - 1;
        while (i < m && j >= 0) {
            if (target == matrix[i][j]) {
                return true;
            }
            else if (target < matrix[i][j]) {
                j -= 1;
            }
            else {
                i += 1;
            }
        }
        return false;
    }
};

int main() {
    Solution s;
    return 0;
}