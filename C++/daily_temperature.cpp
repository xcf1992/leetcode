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
            
            if (tempDate.empty()) {
                result[i] = 0;
            }
            
            tempDate.push(pair<int, int>(temperatures[i], i));
        }
        
        return result;
    }
};
