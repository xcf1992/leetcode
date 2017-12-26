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
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int start = 0;
        int end = nums.size() - 1;
        int result = 0;
        while (end > start) {
            result += (nums[end] - nums[start]);
            start += 1;
            end -= 1;
        }
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}
