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
    void moveZeroes(vector<int>& nums) {
        int zeroP = 0;
        int notZeroP = 0;
        while (notZeroP < nums.size()) {
            if (nums[notZeroP] != 0) {
                nums[zeroP] = nums[notZeroP];
                zeroP++;
            }
            notZeroP++;
        }

        while (zeroP < nums.size()) {
            nums[zeroP] = 0;
            zeroP++;
        }

        return;
    }
};

int main() {
    Solution s;
    return 0;
}