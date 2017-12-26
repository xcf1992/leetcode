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
    int missingNumber(vector<int>& nums) {
        int result = nums.size();
        for (int i = 0; i < nums.size(); i++) {
            result ^= i;
            result ^= nums[i];
        }
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}