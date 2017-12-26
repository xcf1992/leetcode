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
    int arrayNesting(vector<int>& nums) {
        int result = 0;
        int start = 0;
        int temp = 0;
        while (start < nums.size()) {
            if (nums[start] != -1) {
                int num = nums[start];
                nums[start] = -1;
                start = num;
                temp += 1;
            }
            else {
                start = 0;
                result = max(result, temp);
            }
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}
