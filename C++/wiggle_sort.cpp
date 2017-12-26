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
    void wiggleSort(vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) {
            if (i & 1 && nums[i] < nums[i - 1]) {
                swap(nums[i], nums[i - 1]);
            }
            else if (!(i & 1) && nums[i] > nums[i - 1]) {
                swap(nums[i], nums[i - 1]);
            }
        }
        return;
    }
};

int main() {
    Solution s;
    return 0;
}