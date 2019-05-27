/*
40. Combination Sum II

Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.

Each number in candidates may only be used once in the combination.

Note:

All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
Example 1:

Input: candidates = [10,1,2,7,6,1,5], target = 8,
A solution set is:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]
Example 2:

Input: candidates = [2,5,2,1,2], target = 5,
A solution set is:
[
  [1,2,2],
  [5]
]
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
private:
    void generate(vector<int> &num, int target, int sum, int level, vector<int> &solution, vector<vector<int>> &result) {
        if (sum == target) {
            result.push_back(solution);
        }
        
        for (int i = level; i < num.size(); i++) {
            sum += num[i];
            if (sum > target) {
                return;
            }
            solution.push_back(num[i]);
            generate(num, target, sum, i + 1, solution, result);
            solution.pop_back();
            sum -= num[i];
            while (i + 1 < num.size() && num[i + 1] == num[i]) {
                i++;
            }
        }
    }
public:
    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
        vector<vector<int>> result;
        vector<int> solution;
        int sum = 0;
        int level = 0;
        sort(num.begin(), num.end());
        generate(num, target, sum, level, solution, result);
        return result;
    }
};