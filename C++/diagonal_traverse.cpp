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
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        int m = matrix.size();
        if (m == 0) {
            return result;
        }
        int n = matrix[0].size();
        int i = 0;
        int j = 0;
        int backward= 0;

        while (result.size() < m * n) {
            result.push_back(matrix[i][j]);

            if (backward == 0) {
                i--;
                j++;
                if (i < 0 && j <= n - 1) {
                    backward = 1;
                    i += 1;
                }
                else if (j > n - 1) {
                    backward = 1;
                    i += 2;
                    j = n - 1;
                }
            }
            else {
                i++;
                j--;
                if (j < 0 && i <= m - 1) {
                    backward = 0;
                    j += 1;
                }
                else if (i > m - 1) {
                    backward = 0;
                    j += 2;
                    i = m - 1;
                }
            }
        }

        return result;
    }
};