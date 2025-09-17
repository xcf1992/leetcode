/*
1306. Jump Game III
https://leetcode.com/problems/jump-game-iii/

Given an array of non-negative integers arr,
you are initially positioned at start index of the array.
When you are at index i, you can jump to i + arr[i] or i - arr[i],
check if you can reach to any index with value 0.

Notice that you can not jump outside of the array at any time.

Example 1:
Input: arr = [4,2,3,0,3,1,2], start = 5
Output: true
Explanation:
All possible ways to reach at index 3 with value 0 are:
index 5 -> index 4 -> index 1 -> index 3
index 5 -> index 6 -> index 4 -> index 1 -> index 3

Example 2:
Input: arr = [4,2,3,0,3,1,2], start = 0
Output: true
Explanation:
One possible way to reach at index 3 with value 0 is:
index 0 -> index 4 -> index 1 -> index 3

Example 3:
Input: arr = [3,0,2,1,2], start = 2
Output: false
Explanation: There is no way to reach at index 1 with value 0.

Constraints:
1 <= arr.length <= 5 * 10^4
0 <= arr[i] < arr.length
0 <= start < arr.length
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <map>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    bool dfs(vector<int>& memo, vector<int>& arr, int index) {
        if (index < 0 or index >= arr.size()) {
            return false;
        }
        if (arr[index] == 0) {
            return true;
        }
        if (memo[index] != -1) {
            return memo[index] == 1;
        }

        memo[index] = 0;
        if (dfs(memo, arr, index + arr[index]) or dfs(memo, arr, index - arr[index])) {
            memo[index] = 1;
        }
        return memo[index];
    }
public:
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();
        vector<int> memo(n, -1);
        return dfs(memo, arr, start);
    }
};
