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
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, vector<int>> range;
        unordered_map<int, int> frequency;
        int degree = 0;
        for (int i = 0; i < nums.size(); i++) {
            int num = nums[i];
            frequency[num] += 1;
            range[num].push_back(i);
            degree = max(degree, frequency[num]);
        }

        int result = nums.size();
        for (auto it = frequency.begin(); it != frequency.end(); it++) {
            if (degree == it->second) {
                int num = it->first;
                result = min(result, range[num].back() - range[num].front() + 1);
            }
        }
        return result;
    }
};