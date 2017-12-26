#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;


class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int result1 = 0;
        int result2 = 0;

        int xorResult = 0;
        for (auto num : nums) {
            xorResult ^= num;
        }
        int lastBit = xorResult & ((xorResult - 1) ^ xorResult);

        for (auto num : nums) {
            if (lastBit & num) {
                result1 ^= num;
            }
            else {
                result2 ^= num;
            }
        }
        return vector<int>{result1, result2};
    }
};

int main() {
    Solution s;
    return 0;
}