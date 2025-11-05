/*
5127. Remove Covered Intervals
https://leetcode.com/problems/remove-covered-intervals/

Given a list of intervals,
remove all intervals that are covered by another interval in the list.
Interval [a,b) is covered by interval [c,d) if and only if c <= a and b <= d.

After doing so, return the number of remaining intervals.

Example 1:
Input: intervals = [[1,4],[3,6],[2,8]]
Output: 2
Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.

Constraints:
1 <= intervals.length <= 1000
0 <= intervals[i][0] < intervals[i][1] <= 10^5
intervals[i] != intervals[j] for all i != j
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
    int removeCoveredIntervals(vector<vector<int> > &intervals) {
        int n = intervals.size();
        if (n <= 1) {
            return n;
        }

        sort(intervals.begin(), intervals.end(), [](vector<int> &a, vector<int> &b) {
            return a[0] < b[0]
            or(a[0] == b[0] and a[1] < b[1]);
        });

        int result = 1;
        int curEnd = intervals[0][1];
        for (int i = 1; i < n; ++i) {
            if (intervals[i][1] > curEnd) {
                result += 1;
                curEnd = intervals[i][1];
            }
        }
        return result;
    }
};