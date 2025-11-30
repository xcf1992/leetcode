/*
1272. Remove Interval
https://leetcode.com/problems/remove-interval/

Given a sorted list of disjoint intervals,
each interval intervals[i] = [a, b] represents the set of real numbers x such that a <= x < b.

We remove the intersections between any interval in intervals and the interval toBeRemoved.
Return a sorted list of intervals after all such removals.

Example 1:
Input: intervals = [[0,2],[3,4],[5,7]], toBeRemoved = [1,6]
Output: [[0,1],[6,7]]

Example 2:
Input: intervals = [[0,5]], toBeRemoved = [2,3]
Output: [[0,2],[3,5]]

Constraints:
1 <= intervals.length <= 10^4
-10^9 <= intervals[i][0] < intervals[i][1] <= 10^9
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
#include <climits>
#include <set>
using namespace std;

class Solution {
public:
    vector<vector<int>> removeInterval(vector<vector<int>>& intervals, vector<int>& toBeRemoved) {
        int n = intervals.size();
        if (n == 0) {
            return {};
        }

        vector<vector<int>> result;
        int cur = 0;
        for (int i = 0; i < n; ++i, ++cur) {
            if (intervals[i][1] <= toBeRemoved[0]) {
                result.push_back(intervals[i]);
            } else {
                if (intervals[i][0] < toBeRemoved[0]) {
                    result.push_back({intervals[i][0], toBeRemoved[0]});
                }
                break;
            }
        }

        for (int i = cur; i < n; ++i) {
            if (intervals[i][0] <= toBeRemoved[1]) {
                if (intervals[i][1] > toBeRemoved[1]) {
                    result.push_back({toBeRemoved[1], intervals[i][1]});
                }
            } else {
                result.push_back(intervals[i]);
            }
        }
        return result;
    }
};