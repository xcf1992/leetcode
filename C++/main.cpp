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
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        if (nums.empty()) {
            return {to_string(lower) + "->" + to_string(upper)};
        }
        
        if (nums.back() < upper) {
            nums.push_back(upper);
        }
        vector<string> result;
        for (int i = 0; i < nums[i]; ++i) {
            int cur = nums[i];
            if (cur - lower == 2) {
                result.push_back(to_string(lower + 1));
            }
            else if (cur - lower > 2) {
                result.push_back(to_string(lower + 1) + "->" + to_string(cur - 1));
            }
            lower = cur;
        }
        return result;
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
    s.findMissingRanges(temp, 0, 99);
}
