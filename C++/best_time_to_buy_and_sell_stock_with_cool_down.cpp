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
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        int has1_doNothing = -prices[0];
        int has1_sell = 0;
        int has0_doNothing = 0;
        int has0_buy = -prices[0];

        for (int i = 1; i < prices.size(); i++) {
            has1_doNothing = max(has1_doNothing, has0_buy);
            has0_buy = has0_doNothing - prices[i];
            has0_doNothing = max(has0_doNothing, has1_sell);
            has1_sell = has1_doNothing + prices[i];
        }

        return max(has1_sell, has0_doNothing);
    }
};

int main() {
    Solution s;
    return 0;
}