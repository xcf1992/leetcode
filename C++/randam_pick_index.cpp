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
private:
    vector<int> nums;

public:
    Solution(vector<int> nums) {
        this->nums = nums;
    }

    int pick(int target) {
        int result;

        for (int i = 0, cnt = 1; i < nums.size(); i++) {
            if (nums[i] == target and ((rand() % cnt++) == 0)) {
                result = i;
            }
        }

        return result;
    }
};

/*
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * int param_1 = obj.pick(target);
*/

int main() {
    Solution s;
    return 0;
}