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
    bool isPerfectSquare(int num) {
        int left = 0;
        int right = num;
        while (left <= right) {
            long mid = left + (right - left) / 2;
            if (mid * mid == (long) num) {
                return true;
            }
            
            if (mid * mid > num) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return false;
    }
};

class Solution1 {
public:
    bool isPerfectSquare(int num) {
        int diff = 1;
        int cur = 0;
        while (cur <= num && cur >= 0) {
            if (cur == num) {
                return true;
            }

            cur += diff;
            diff += 2;
        }

        return false;
    }
};

int main() {
    Solution s;
    return 0;
}