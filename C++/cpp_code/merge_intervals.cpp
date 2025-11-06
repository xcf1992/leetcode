/*
56. Merge Intervals
https://leetcode.com/problems/merge-intervals/

Given a collection of intervals, merge all overlapping intervals.

Example 1:
Input: [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].

Example 2:
Input: [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.

NOTE:
input types have been changed on April 15, 2019.
Please reset to default code definition to get new method signature.
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
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if (n <= 1) {
            return intervals;
        }

        sort(intervals.begin(), intervals.end(),
             [](vector<int>& a, vector<int>& b) { return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]); });

        vector<vector<int>> result;
        int start = intervals[0][0];
        int end = intervals[0][1];
        for (int i = 1; i < n; ++i) {
            if (end < intervals[i][0]) {
                result.push_back({start, end});
                start = intervals[i][0];
                end = intervals[i][1];
                continue;
            }
            end = max(end, intervals[i][1]);
        }
        result.push_back({start, end});
        return result;
    }
};
