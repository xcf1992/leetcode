/*
216. Combination Sum III
https://leetcode.com/problems/combination-sum-iii/

Find all possible combinations of k numbers that add up to a number n,
given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.

Note:
All numbers will be positive integers.
The solution set must not contain duplicate combinations.

Example 1:
Input: k = 3, n = 7
Output: [[1,2,4]]

Example 2:
Input: k = 3, n = 9
Output: [[1,2,6], [1,3,5], [2,3,4]]
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
#include <climits>
using namespace std;

class Solution {
private:
    void dfs(vector<vector<int>>& result, vector<int> combination, int k, int target, int start) {
        if (k == 0 and target == 0) {
            result.push_back(combination);
            return;
        }
        if (start > target or k <= 0) {
            return;
        }

        for (int i = start; i <= 9; i++) {
            combination.push_back(i);
            dfs(result, combination, k - 1, target - i, i + 1);
            combination.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> result;
        vector<int> combination;
        dfs(result, combination, k, n, 1);
        return result;
    }
};