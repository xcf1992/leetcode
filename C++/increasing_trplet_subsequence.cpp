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
    bool increasingTriplet(vector<int>& nums) {
        int smallest = INT_MAX;
        int smaller = INT_MAX;
        for (int n : nums) {
            if (n <= smallest) {
                smallest = n;
            }
            else if (n <= smaller) {
                smaller = n;
            }
            else {
                return true;
            }
        }
        return false;
    }
};

int main() {
    Solution s;
    return 0;
}