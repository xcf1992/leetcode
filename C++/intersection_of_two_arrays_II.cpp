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
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        std::vector<int> result;
        unordered_map<int, int> intersection;
        for (int i = 0; i < nums1.size(); i++) {
            intersection[nums1[i]] += 1;
        }

        for (int i = 0; i < nums2.size(); i++) {
            if (intersection.find(nums2[i]) != intersection.end() && intersection[nums2[i]] > 0) {
                result.push_back(nums2[i]);
                intersection[nums2[i]] -= 1;
            }
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}