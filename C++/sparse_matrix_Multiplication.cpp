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
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        int m = A.size();
        int n = A[0].size();
        vector<vector<int>> result(m, vector<int>(B[0].size(),0));

        for (int i = 0; i < m; i++) {
            for (int k = 0; k < n; k++) {
                for (int j = 0; j < n; j++) {
                    result[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}