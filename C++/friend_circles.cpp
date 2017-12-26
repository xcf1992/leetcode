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
    void visit(vector<vector<int>>& M, vector<bool>& visited, int start) {
        visited[start] = true;
        for (int i = 0; i < M[0].size(); i++) {
            if (!visited[i] && M[start][i]) {
                visit(M, visited, i);
            }
        }
    }

public:
    int findCircleNum(vector<vector<int>>& M) {
        vector<bool> visited(M.size(), false);
        int result = 0;
        for (int i = 0; i < M.size(); i++) {
            if (!visited[i]) {
                visited[i] = true;
                result += 1;
                for (int j = 0; j < M[0].size(); j++) {
                    if (!visited[j] && M[i][j]) {
                        visit(M, visited, j);
                    }
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
