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
    int findMaxLength(vector<int>& nums) {
        int n = nums.size();
        vector<int> diff(n + 1, 0);
        unordered_map<int, int> pos;

        int result = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                diff[i + 1] = diff[i] - 1;
            } else {
                diff[i + 1] = diff[i] + 1;
            }

            if (diff[i + 1] == 0) {
                result = max(result, i + 1);
            }

            if (pos.find(diff[i + 1]) == pos.end()) {
                pos[diff[i + 1]] = i;
            } else {
                result = max(result, i - pos[diff[i + 1]]);
            }
        }

        return result;
    }
};