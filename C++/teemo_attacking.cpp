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
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        if (timeSeries.empty()) {
            return 0;
        }
        int result = 0;
        for (int i = 0; i < timeSeries.size() - 1; i++) {
            if (timeSeries[i] + duration - 1 >= timeSeries[i + 1]) {
                result += timeSeries[i + 1] - timeSeries[i];
            }
            else {
                result += duration;
            }
        }
        return result + duration;
    }
};

int main() {
    Solution s;
    return 0;
}
