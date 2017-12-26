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

struct mycompare {
    bool operator () (pair<int, int>& a, pair<int, int>& b) {
        return a.second >= b.second;
    }
};

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, mycompare> pq;
        vector<int> result(2, 0);

        int large = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            large = max(large, nums[i][0]);
            pq.push({i, nums[i][0]});
        }

        int maxLen = INT_MAX;
        vector<int> index(nums.size() , 0);
        while (pq.size() == nums.size()) {
            int row = pq.top().first;
            int cur = pq.top().second;
            pq.pop();

            if (large - cur < maxLen) {
                maxLen = large - cur;
                result[0] = cur;
                result[1] = large;
            }

            if (index[row] + 1 < nums[row].size()) {
                index[row] += 1;
                pq.push({row, nums[row][index[row]]});
                large = max(large, nums[row][index[row]]);
            }

        }

        return result;
    }
};