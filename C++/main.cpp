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

class Solution { // dp
public:
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        map<int, unordered_set<int>> reach;
        unordered_set<int> s(stones.begin(), stones.end());
        reach[stones.front()].insert(0);

        for (int i = 0; i < n; ++i) {
            for (int k : reach[stones[i]]) {
                for (int step = max(0, k - 1); step <= k + 1; ++step) {
                    if (s.find(step + stones[i]) != s.end()) {
                        reach[stones[i] + step].insert(step);
                    }
                }
            }
        }
        return reach[stones.back()].size() > 0;
    }
};

int main() {
    Solution s;
    vector<int> temp({5,4,3,2,1});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<char>> matrix({
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    });
}
