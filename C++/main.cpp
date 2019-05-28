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
    bool canTransform(string start, string end) {
        int n = start.size();
        int pos1 = 0;
        int pos2 = 0;
        while (pos1 < n and pos2 < n) {
            while (pos1 < n and start[pos1] == 'X') {
                pos1 += 1;
            }
            while (pos2 < n and start[pos2] == 'X') {
                pos2 += 1;
            }

            // if one of the pos index goes to the end while the other is not,
            // we should return false
            if ((pos1 < n) ^ (pos2 < n)) {
                return false;
            }

            if (pos1 < n and pos2 < n) {
                if (start[pos1] != end[pos2]) {
                    return false;
                }

                if (start[pos1] == 'L' and pos1 < pos2) {
                    return false;
                }

                if (start[pos1] == 'R' and pos1 > pos2) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    Solution s;
    vector<int> temp({0,1,3,50,75});
    vector<vector<int>> matrix({
        {1,2,3},
        {4,5,6},
        {7,8,9}
    });
    s.canTransform("X", "L");
}
