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
    int integerBreak(int n) {
        vector<int> maxProduct(n + 1, 0);
        maxProduct[2] = 1;

        for (int i = 3; i <= n; i++) {
            for (int j = 1; j < i; j++) {
                maxProduct[i] = max(maxProduct[i], max(j * (i - j), j * maxProduct[i - j]));
            }
        }

        return maxProduct[n];
    }
};

int main() {
    Solution s;
    return 0;
}