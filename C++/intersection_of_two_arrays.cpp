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
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        unordered_set<int> intersection1;
        unordered_set<int> intersection2;

        for (int i = 0; i < nums1.size(); i++) {
            intersection1.insert(nums1[i]);
        }

        for (int i = 0; i < nums2.size(); i++) {
            intersection2.insert(nums2[i]);
        }

        for (auto it = intersection1.begin(); it != intersection1.end(); it++) {
            if (intersection2.find(*it) != intersection2.end()) {
                result.push_back(*it);
            }
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}