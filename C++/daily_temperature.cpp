/*
739. Daily Temperatures
Given a list of daily temperatures T,
return a list such that,
for each day in the input,
tells you how many days you would have to wait until a warmer temperature.
If there is no future day for which this is possible, put 0 instead.

For example, given the list of temperatures
T = [73, 74, 75, 71, 69, 72, 76, 73],
your output should be [1, 1, 4, 2, 1, 1, 0, 0].

Note: The length of temperatures will be in the range [1, 30000].
Each temperature will be an integer in the range [30, 100].
*/
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
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<pair<int, int>> tempDate;
        vector<int> result(temperatures.size(), 0);
        for (int i = temperatures.size() - 1; i >= 0; i--) {
            while (!tempDate.empty()) {
                pair<int, int> warmer = tempDate.top();
                if (temperatures[i] < warmer.first) {
                    result[i] = warmer.second - i;
                    break;
                }
                else {
                    tempDate.pop();
                }
            }
            tempDate.push({temperatures[i], i});
        }
        return result;
    }
};
