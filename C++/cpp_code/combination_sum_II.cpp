/*
40. Combination Sum II
https://leetcode.com/problems/combination-sum-ii/

Given a collection of candidate numbers (candidates) and a target number (target),
find all unique combinations in candidates where the candidate numbers sums to target.
Each number in candidates may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
The combination set must not contain duplicate combinations.

Example 1:
Input: candidates = [10,1,2,7,6,1,5], target = 8,
A combination set is:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]

Example 2:
Input: candidates = [2,5,2,1,2], target = 5,
A combination set is:
[
  [1,2,2],
  [5]
]
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
private:
    void dfs(vector<int>& num, int target, int level, vector<int>& combination, vector<vector<int>>& result) {
        if (target == 0) {
            result.push_back(combination);
            return;
        }

        for (int i = level; i < num.size(); i++) {
            if (num[i] > target) {
                return;
            }
            combination.push_back(num[i]);
            dfs(num, target - num[i], i + 1, combination, result);
            combination.pop_back();
            while (i + 1 < num.size() and num[i + 1] == num[i]) {
                i++;
            }
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& num, int target) {
        vector<vector<int>> result;
        vector<int> combination;
        sort(num.begin(), num.end());
        dfs(num, target, 0, combination, result);
        return result;
    }
};