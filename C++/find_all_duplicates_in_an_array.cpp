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
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> result;

        int i = 0;
        while (i < nums.size()) {
            int current = nums[i];
            if (current == i + 1 || current == 0) {
                i++;
            }
            else {
                if (current == nums[current - 1]) {
                    result.push_back(current);
                    nums[current - 1] = 0;
                    i++;
                }
                else {
                    swap(nums[i], nums[current - 1]);
                }
            }
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}
