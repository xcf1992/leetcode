/*
1215. Stepping Numbers
https://leetcode.com/problems/stepping-numbers/

A Stepping Number is an integer such that all of its adjacent digits have an absolute difference of exactly 1.
For example, 321 is a Stepping Number while 421 is not.

Given two integers low and high, find and return a sorted list of all the Stepping Numbers in the range [low, high]
inclusive.

Example 1:
Input: low = 0, high = 21
Output: [0,1,2,3,4,5,6,7,8,9,10,12,21]

Constraints:
0 <= low <= high <= 2 * 10^9
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    vector<int> countSteppingNumbers(int low, int high) {
        queue<long> bfs;
        for (int i = 1; i <= 9; ++i) {
            bfs.push(i);
        }

        vector<int> result;
        if (low == 0) {
            result.push_back(0);
        }
        while (!bfs.empty()) {
            long cur = bfs.front();
            bfs.pop();

            if (cur > high) {
                continue;
            }

            if (cur >= low) {
                result.push_back(cur);
            }
            int last = cur % 10;
            if (last > 0) {
                bfs.push(cur * 10 + last - 1);
            }
            if (last < 9) {
                bfs.push(cur * 10 + last + 1);
            }
        }
        return result;
    }
};