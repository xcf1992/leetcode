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
    int calculate(vector<int>& position) {
        int result = 0;

        int middle = position[position.size() / 2];
        for (int i = 0; i < position.size(); i++) {
            result += abs(position[i] - middle);
        }

        return result;
    }
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        vector<int> row;
        vector<int> col;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    row.push_back(i);
                    col.push_back(j);
                }
            }
        }

        sort(col.begin(), col.end());

        return calculate(row) + calculate(col);
    }
};

int main() {
    Solution s;
    return 0;
}