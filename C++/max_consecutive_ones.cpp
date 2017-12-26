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
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int result = 0;
        int current = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 1) {
                current += 1;
            }
            else {
                result = max(result, current);
                current = 0;
            }
        }
        return max(result, current);
    }
};

int main() {
    Solution s;
    return 0;
}
