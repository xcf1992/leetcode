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
    unordered_map<int, int> combination;
public:
    int combinationSum4(vector<int>& nums, int target) {
        if (combination.find(target) != combination.end()) {
            return combination[target];
        }
        if (target == 0) {
            return 1;
        }
        if (target < 0) {
            return 0;
        }

        int result = 0;
        for (int i = 0; i < nums.size(); i++) {
            result += combinationSum4(nums, target - nums[i]);
        }
        combination[target] = result;

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}