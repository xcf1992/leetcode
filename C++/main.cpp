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
#include <map>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int> nums1, vector<int> nums2, int k) {
        if (nums1.empty() || nums2.empty()) {
            return {};
        }

        int len1 = nums1.size();
        int len2 = nums2.size();
        auto comp = [](vector<int>& a, vector<int>& b) {
            return a[2] > b[2];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> minHeap(comp);
        for (int j = 0; j < len2; ++j) {
            minHeap.push({0, j, nums1[0] + nums2[j]});
        }

        vector<vector<int>> result;
        for(int i = 0; i < min(k, len1 * len2); i++) {
            vector<int> pair = minHeap.top();
            minHeap.pop();
            result.push_back({nums1[pair[0]], nums2[pair[1]]});

            if (pair[0] + 1 < len1) {
                int sum = nums1[pair[0] + 1] + nums2[pair[0]];
                minHeap.push({pair[0] + 1, pair[1], sum});
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({0,1,3,50,75});
    vector<vector<int>> matrix({{8,2},{4,2},{4,5},{2,0},{7,2},{1,4},{9,1},{3,1},{9,0},{1,0}});
    s.kSmallestPairs({-10,-4,0,0,6}, {3,5,6,7,8,100}, 10);
}
