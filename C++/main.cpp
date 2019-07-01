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
    vector<int> pathInZigZagTree(int label) {
        int level = 1;
        while ((1 << level) <= label) {
            level += 1;
        }
        
        vector<int> result(level, 1);
        for (; label > 1; label /= 2) {
            result[level - 1] = label;
            level -= 1;
            int parentStart = 1 << (level - 1);
            int parentEnd = (1 << level) - 1;
            label = parentEnd - (label / 2 - parentStart);
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({1,3,2,4});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {0,1},
        {1,2},
        {2,1},
        {1,0},
        {0,2},
        {0,0},
        {1,1}
    });
    vector<vector<int>> matrix2({
        {1,0},
        {0,0}
    });
    vector<string> words({"cat","cats","and","sand","dog"});
    s.pathInZigZagTree(14);
}
