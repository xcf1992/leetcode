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
private:
    int count(int x, int y, vector<vector<int>>& M) {
        int sum = M[x][y];
        int num = 1;
        if (x - 1 >= 0 and y - 1 >= 0) {
            sum += M[x - 1][y - 1];
            num += 1;
        }
        if (x - 1 >= 0) {
            sum += M[x - 1][y];
            num += 1;
        }
        if (x - 1 >= 0 and y + 1 < M[0].size()) {
            sum += M[x - 1][y + 1];
            num += 1;
        }
        if (y - 1 >= 0) {
            sum += M[x][y - 1];
            num += 1;
        }
        if (y + 1 < M[0].size()) {
            sum += M[x][y + 1];
            num += 1;
        }
        if (x + 1 < M.size() and y - 1 >= 0) {
            sum += M[x + 1][y - 1];
            num += 1;
        }
        if (x + 1 < M.size()) {
            sum += M[x + 1][y];
            num += 1;
        }
        if (x + 1 < M.size() and y + 1 < M[0].size()) {
            sum += M[x + 1][y + 1];
            num += 1;
        }
        return sum / num;
    }
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& M) {
        vector<vector<int>> result(M.size(), vector<int>(M[0].size(), 0));
        for (int i = 0; i < M.size(); i++) {
            for (int j = 0; j < M[0].size(); j++) {
                result[i][j] = count(i, j, M);
            }
        }
        return result;
    }
};