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
    int minMoves(vector<int>& nums) {
        int sum = 0;
        int minNum = INT_MAX;
        for (int num : nums) {
            sum += num;
            minNum = min(minNum, num);
        }

        return sum - nums.size() * minNum;
    }
};

int main() {
    Solution s;
    return 0;
}
