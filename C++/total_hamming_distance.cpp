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
    int totalHammingDistance(vector<int>& nums) {
        int result = 0;
        int count = nums.size();
        for (int i = 0; i < 32; i++) {
            int zeroCount = 0;
            for (int num : nums) {
                if (num & 1 == 0) {
                    zeroCount += 1;
                    num >>= 1;
                }
            }
            result += zeroCount * (count - zeroCount);
        }
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}
