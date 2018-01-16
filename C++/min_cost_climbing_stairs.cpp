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
    int minCostClimbingStairs(vector<int>& cost) {
        int oneStep = 0;
        int twoStep = 0;
        int fee = 0;
        for (int curFee : cost) {
            fee = min(oneStep, twoStep) + curFee;
            twoStep = oneStep;
            oneStep = fee;
        }
        return min(oneStep, twoStep);
    }
};
