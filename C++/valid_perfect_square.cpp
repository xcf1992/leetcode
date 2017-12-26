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