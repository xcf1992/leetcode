/*
216. Combination Sum III

Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.

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
#include <stdio.h>
using namespace std;

class Solution {
private:
    void getCombinations(vector<vector<int>>& result, vector<int> combination, int k, int target, int start) {
        if (k == 0 && target == 0) {
            result.push_back(combination);
            return;
        }

        if (start > target || k < 0) {
            return;
        }

        for (int i = start; i <= 9; i++) {
            combination.push_back(i);
            getCombinations(result, combination, k - 1, target - i, i + 1);
            combination.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> result;
        vector<int> combination; 
        getCombinations(result, combination, k, n, 1);
        return result;
    }
};
