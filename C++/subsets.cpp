/*
78. Subsets
Given a set of distinct integers, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

Example:

Input: nums = [1,2,3]
Output:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
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

class Solution { // bit manipulation
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        int count = 1 << n;
        vector<vector<int>> result(count);
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < n; j++) {
                if ((i >> j) & 1) {
                    result[i].push_back(nums[j]);
                }
            }
        }
        return result;
    }
};

class Solution1 { //5.58%
private:
    void construct(vector<int> &S, int index, vector<vector<int>>& result, vector<int> current) {
        if (index == S.size()) {
            result.push_back(current);
            return;
        }

        current.push_back(S[index]);
        construct(S, index + 1, result, current);
        current.pop_back();
        construct(S, index + 1, result, current);
    }
public:
    vector<vector<int>> subsets(vector<int>& S) {
        if (S.empty()) {
            return {};
        }
        vector<vector<int>> result;
        construct(S, 0, result, {});
        return result;
    }
};
