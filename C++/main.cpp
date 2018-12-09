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
public:
    int minDeletionSize(vector<string> A) {
        int result = 0;
        int n = A[0].size();
        for (int col = 0; col < n; col++) {
            bool pass = true;
            for (int row = 1; row < A.size(); row++) {
                if (A[row][col] < A[row - 1][col]) {
                    pass = false;
                    break;
                }
            }
            if (pass) {
                return true;
            }
            result += 1;
        }
        return result;
    }
};

int main() {
    vector<bool> visited(10, false);
    visited[2] = true;
    visited[7] = true;
    visited[4] = true;
    visited.resize(10, false);
    visited.clear();
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
    vector<vector<int>> vb({{3,0}});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({
        {1,1,1,0,1,1,1,1},
        {1,0,0,0,0,1,1,1},
        {1,1,1,0,0,0,1,1},
        {1,1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0}
    });
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    vector<vector<int>> matrix3({
        {1,0},
        {0,1}
    });
    s.minDeletionSize({"xc","yb","za"});
    return 0;
}
