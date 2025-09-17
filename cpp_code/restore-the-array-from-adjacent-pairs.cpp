/*
1743. Restore the Array From Adjacent Pairs
https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/

There is an integer array nums that consists of n unique elements,
but you have forgotten it.
However, you do remember every pair of adjacent elements in nums.

You are given a 2D integer array adjacentPairs of size n - 1
where each adjacentPairs[i] = [ui, vi] indicates
that the elements ui and vi are adjacent in nums.

It is guaranteed that every adjacent pair of elements nums[i]
and nums[i+1] will exist in adjacentPairs, either as [nums[i], nums[i+1]] or [nums[i+1], nums[i]].
The pairs can appear in any order.

Return the original array nums.
If there are multiple solutions, return any of them.

Example 1:
Input: adjacentPairs = [[2,1],[3,4],[3,2]]
Output: [1,2,3,4]
Explanation: This array has all its adjacent pairs in adjacentPairs.
Notice that adjacentPairs[i] may not be in left-to-right order.
Example 2:
Input: adjacentPairs = [[4,-2],[1,4],[-3,1]]
Output: [-2,4,1,-3]
Explanation: There can be negative numbers.
Another solution is [-3,1,4,-2], which would also be accepted.
Example 3:
Input: adjacentPairs = [[100000,-100000]]
Output: [100000,-100000]

Constraints:
nums.length == n
adjacentPairs.length == n - 1
adjacentPairs[i].length == 2
2 <= n <= 105
-105 <= nums[i], ui, vi <= 105
There exists some nums that has adjacentPairs as its pairs.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
#include <bitset>
using namespace std;

class Solution {
public:
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {
        unordered_map<int, vector<int> > ps;
        for (auto &p : adjacentPairs) {
            ps[p[0]].push_back(p[1]);
            ps[p[1]].push_back(p[0]);
        }

        vector<int> res;
        for (auto &p : ps) {
            if (p.second.size() == 1) {
                res.push_back(p.first);
                res.push_back(p.second[0]);
                break;
            }
        }

        while (res.size() < adjacentPairs.size() + 1) {
            auto tail = res.back(), prev = res[res.size() - 2];
            auto &next = ps[tail];
            if (next[0] != prev)
                res.push_back(next[0]);
            else
                res.push_back(next[1]);
        }
        return res;
    }
};
