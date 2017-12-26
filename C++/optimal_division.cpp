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
    string optimalDivision(vector<int>& nums) {
        string result = "";
        if (nums.size() == 0) {
            return result;  
        }

        result = to_string(nums[0]);
        if (nums.size() == 1) {
            return result;
        }
        if (nums.size() == 2) {
            return result + "/" + to_string(nums[1]);
        }

        result += "/(" + to_string(nums[1]);
        for (int i = 2; i < nums.size(); ++i) {
            result += "/" + to_string(nums[i]);
        }

        result += ")";
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}
