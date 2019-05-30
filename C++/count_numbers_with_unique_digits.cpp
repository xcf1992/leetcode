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
    int countNumbersWithUniqueDigits(int n) {
        vector<int> result(n + 1, 0);
        result[0] = 1;
        int multiplier = 9;

        for (int i = 1; i <= n; i++) {
            result[i] = result[i - 1] + multiplier;
            if (i <= 9) {
                multiplier *= (10 - i);
            }
            else {
                multiplier = 0;
            }
        }

        return result[n];
    }
};

int main() {
    Solution s;
    return 0;
}