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
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, -1);
        stack<int> bigger;

        for (int i = 0; i < 2 * n; i++) {
            int num = nums[i % n];

            while (bigger.size() != 0 && nums[bigger.top()] < num) {
                result[bigger.top()] = num;
                bigger.pop();
            }

            if (i < n) {
                bigger.push(i);
            }
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}
