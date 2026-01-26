/*
https://leetcode.com/problems/permutations-iii/description/
3437. Permutations III

Given an integer n, an alternating permutation is a permutation of the first n positive integers such that no two
adjacent elements are both odd or both even.

Return all such alternating permutations sorted in lexicographical order.



Example 1:

Input: n = 4

Output: [[1,2,3,4],[1,4,3,2],[2,1,4,3],[2,3,4,1],[3,2,1,4],[3,4,1,2],[4,1,2,3],[4,3,2,1]]

Example 2:

Input: n = 2

Output: [[1,2],[2,1]]

Example 3:

Input: n = 3

Output: [[1,2,3],[3,2,1]]



Constraints:

1 <= n <= 10
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
    void backtrack(int n, vector<int>& current, vector<bool>& used, vector<vector<int>>& result) {
        // Base case: found a complete permutation
        if (current.size() == n) {
            result.push_back(current);
            return;
        }

        // Try adding each unused number
        for (int num = 1; num <= n; num++) {
            if (used[num]) {
                continue;
            }

            // Check if adding this number maintains alternating property
            if (!current.empty()) {
                if ((current.back() % 2) == (num % 2)) {
                    continue;
                }
            }

            current.push_back(num);
            used[num] = true;
            backtrack(n, current, used, result);
            current.pop_back();
            used[num] = false;
        }
    }

public:
    // Approach 1: Backtracking with Parity Check
    vector<vector<int>> permute(int n) {
        vector<vector<int>> rst;
        vector<int> current;
        vector<bool> used(n + 1, false);
        backtrack(n, current, used, rst);
        // Results are automatically in lexicographical order due to exploring in ascending order
        return rst;
    }
};