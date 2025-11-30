#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> result;

        for (int i = 0; i < nums.size(); i++) {
            int value = abs(nums[i]);
            nums[value - 1] = -1 * abs(nums[value - 1]);
        }

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) {
                result.push_back(i + 1);
            }
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}