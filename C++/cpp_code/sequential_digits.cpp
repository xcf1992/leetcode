/*
1291. Sequential Digits
https://leetcode.com/problems/sequential-digits/

An integer has sequential digits if and only if each digit in the number is one more than the previous digit.
Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.

Example 1:
Input: low = 100, high = 300
Output: [123,234]

Example 2:
Input: low = 1000, high = 13000
Output: [1234,2345,3456,4567,5678,6789,12345]

Constraints:
10 <= low <= high <= 10^9
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
#include <map>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

// maybe is better to bfs to solve this question, then we do not need to do sort at last
class Solution {
private:
    void dfs(vector<int>& result, int low, int high, int cur, int num) {
        if (num >= high) {
            return;
        }

        if (num >= low) {
            result.push_back(num);
        }

        if (cur == 10) {
            return;
        }

        num = num * 10 + cur;
        dfs(result, low, high, cur + 1, num);
    }

public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> result;
        for (int i = 1; i <= 8; ++i) {
            dfs(result, low, high, i, 0);
        }
        sort(result.begin(), result.end());
        return result;
    }
};