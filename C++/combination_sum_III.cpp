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
    vector<vector<int>> combinations;
    
    void getCombinations(vector<int> combination, int k, int target, int start) {
        if (k == 0 && target == 0) {
            combinations.push_back(combination);
            return;
        }

        if (start > target || k < 0) {
            return;
        }

        for (int i = start; i <= 9; i++) {
            combination.push_back(i);
            getCombinations(combination, k - 1, target - i, i + 1);
            combination.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> combination;
        
        getCombinations(combination, k, n, 1);

        return combinations;
    }
};

int main() {
    Solution s;
    return 0;
}