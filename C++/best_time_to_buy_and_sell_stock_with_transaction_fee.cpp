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
    int maxProfit(vector<int>& prices, int fee) {
        int haveStockProfit = INT_MIN;
        int noStockProfit = 0;
        for (int price : prices) {
            int temp = noStockProfit;
            noStockProfit = max(noStockProfit, haveStockProfit + price);
            haveStockProfit = max(haveStockProfit, temp - pricee - fee);
        }
        return noStockProfit;
    }
};
