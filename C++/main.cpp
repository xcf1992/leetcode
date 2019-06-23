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
public:
    vector<int> gridIllumination(int N, vector<vector<int>> lamps, vector<vector<int>> queries) {
        unordered_map<int, int> row, col, diagonal, antiDiagonal;
        unordered_map<int, unordered_set<int>> onLamps;
        for (vector<int>& lamp : lamps) {
            int r = lamp[0];
            int c = lamp[1];
            row[r] += 1;
            row[c] += 1;
            diagonal[r + c] += 1;
            antiDiagonal[r - c] += 1;
            onLamps[r].insert(c);
        }
        
        vector<int> result;
        for (vector<int>& query : queries) {
            int r = query[0];
            int c = query[1];
            if (row[r] != 0 or col[c] != 0 or diagonal[r + c] != 0 or antiDiagonal[r - c] != 0) {
                result.push_back(1);
                for (int i = r - 1; i <= r + 1; ++i) {
                    for (int j = c - 1; j <= c + 1; ++j) {
                        if (onLamps[i].erase(j)) {
                            row[i] -= 1;
                            col[j] -= 1;
                            diagonal[i + j] -= 1;
                            antiDiagonal[i - j] -= 1;
                        }
                    }
                }
            }
            else {
                result.push_back(0);
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({1,3,2,4});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<char>> matrix({
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    });
    vector<string> words({"cat","cats","and","sand","dog"});
    s.gridIllumination(5, {{0,0},{4,4}}, {{1,1},{1,0}});
}
