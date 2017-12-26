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
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        if (ops.empty()) {
            return m * n;
        }
        int l = INT_MAX;
        int w = INT_MAX;
        for (auto op : ops) {
            l = min(l, op[0]);
            w = min(w, op[1]);
        }

        return l * w;
    }
};

int main() {
    Solution s;
    return 0;
}
